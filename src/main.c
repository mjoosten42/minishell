/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/17 11:08:13 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
		system("leaks minishell");
}

int	main(void)
{
	char	*str;

	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		add_history(str);
		ft_execute(str);
		free(str);
	}
	ft_putchar_fd(BACKSPACE, 0);
	ft_putchar_fd(BACKSPACE, 0);
	ft_putstr("exit\n");
	exit(EXIT_SUCCESS);
}

void	ft_execute(char *str)
{
	pid_t		pid;
	char		**strs;
	char		*path;

	strs = ft_split(str, ' ');
	if (!strs)
		ft_error(NULL);
	path = ft_getpath(*strs);
	if (!path)
		return ;
	pid = fork();
	if (!pid)
		if (execve(path, strs, 0) < 0)
			ft_error(NULL);
	waitpid(pid, 0, 0);
	ft_free_array(strs);
	free(path);
}

char	*ft_getpath(char *str)
{
	static char	**paths;
	char		*path;
	int			i;

	i = 0;
	if (!paths)
		paths = ft_getpaths();
	if (!access(str, F_OK))
		return (ft_strdup(str));
	while (paths[i])
	{
		path = ft_strjoin(paths[i], str);
		if (!access(path, F_OK))
			return (path);
		free(path);
		i++;
	}
	ft_putstr_fd(rl_line_buffer, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

char	**ft_getpaths(void)
{
	char	**strs;
	char	*str;
	int		i;

	i = 0;
	strs = ft_split(getenv("PATH"), ':');
	if (!strs)
		ft_error(NULL);
	while (strs[i])
	{
		str = ft_strjoin(strs[i], "/");
		free(strs[i]);
		strs[i] = str;
		i++;
	}
	return (strs);
}
