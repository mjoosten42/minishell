/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/28 13:10:21 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

t_program_data	g_pd;

int	main(void)
{
	extern int		rl_catch_signals;
	t_token			*head;
	char			*str;

	rl_catch_signals = 0;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	copy_env();
	getcwd(g_pd.dir, PATH_MAX);
	while (1)
	{
		head = NULL;
		str = readline("minishell$ ");
		if (!str)
			ft_exit();
		if (*str)
			add_history(str);
		lexer(&head, str);
		ft_expand(&head);
		print_tokens(head);
		ft_parse(&head);
		free(str);
	}
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
}

void	print_tokens(t_token *token)
{
	char	*types[] = {
		"pipe_char",
		"red_in",
		"red_out",
		"dollar",
		"dquote",
		"quote",
		"space",
		"tab",
		"newline",
		"here_doc",
		"red_out_app",
		"word"
	};

	printf(" - id -------- type - value\n");
	while (token)
	{
		printf(" | %2i | %11s | [%s]\n",
			token->position, types[token->type], token->value);
		token = token->next;
	}
	printf("\n");
}
