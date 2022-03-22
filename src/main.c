/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/22 16:39:25 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	copy_env(t_program_data *pd, char **env)
{
	int	amount_env_lines;

	amount_env_lines = 0;
	while (env[amount_env_lines] != NULL)
		amount_env_lines++;
	pd->amount_env_lines = amount_env_lines;
	pd->env = ft_malloc((amount_env_lines + 1) * sizeof(char *));
	amount_env_lines = 0;
	while (env[amount_env_lines] != NULL)
	{
		pd->env[amount_env_lines] = ft_strdup(env[amount_env_lines]);
		amount_env_lines++;
	}
	pd->env[amount_env_lines] = NULL;
}

int	main(int argc, char *argv[], char *env[])
{
	t_program_data	program_data;
	t_token	*head;
	char	*str;

	rl_catch_signals = 0;
	ignal(SIGINT, ft_signal);
	ignal(SIGQUIT, ft_signal);
	copy_env(&program_data, env);
	while (1)
	{
		head = 0;
		str = readline("minishell$ ");
		if (!str)
			break ;
		if (!*str)
		{
			free(str);
			continue ;
		}
		add_history(str);
		lexer(&head, str);
		ft_parse(&head);
		free(str);
	}
	ft_putstr("exit\n");
	exit(EXIT_SUCCESS);
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
		"word",
		"pipe_char",
		"red_in",
		"red_out",
		"here_doc",
		"red_out_app",
		"dollar",
		"dquote",
		"quote",
		"space",
		"tab",
		"newline"
	};
	printf("\n- id -------- type - value\n");
	while (token)
	{
		printf("| %2i | %11s | [%s]\n", token->position, types[token->type], token->value);
		token = token->next;
	}
	printf("\n");
}
