/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/01 14:31:58 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

t_program_data	g_pd;

void	copy_env(void);
void	ft_signal(int signum);

int	main(void)
{
	extern int	rl_catch_signals;
	t_token		*head;
	char		*str;

	copy_env();
	rl_catch_signals = 0;
	//signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	signal(SIGCHLD, ft_signal);
	getcwd(g_pd.dir, PATH_MAX);
	while (1)
	{
		head = NULL;
		str = readline("minishell$ ");
		if (!str)
			ft_exit(NULL);
		if (*str)
			add_history(str);
		lexer(&head, str);
		ft_expand(&head);
		print_tokens(head);
		ft_parse(&head, STDIN_FILENO);
		free(str);
	}
}

pid_t	ft_exec(char **args, int fds[2])
{
	pid_t	pid;
	char	*path;

	if (!ft_strncmp(*args, "exit", 5))
		ft_exit(args[1]);
	pid = fork();
	if (pid < 0)
		ft_error(NULL);
	if (!pid)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		if (is_builtin(args))
			exit(EXIT_SUCCESS);
		path = ft_getpath(*args);
		if (!path)
			ft_error(ft_strjoin(*args, ": command not found"));
		execve(path, args, g_pd.env);
		ft_error(0);
	}
	if (fds[0] > 2)
		close(fds[0]);
	if (fds[1] > 2)
		close(fds[1]);
	return (pid);
}

void	copy_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	g_pd.amount_env_lines = i;
	g_pd.env = ft_malloc((i + 1) * sizeof(char *));
	g_pd.env[i] = NULL;
	while (i--)
		g_pd.env[i] = ft_strdup(environ[i]);
}

void	ft_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGCHLD)
		wait(NULL);
}
