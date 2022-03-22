/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/22 16:32:13 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	print_env(char **env)
{
	int	current_line;

	current_line = 0;
	while (env[current_line] != NULL)
	{
		printf("%s\n", env[current_line]);
		current_line++;
	}
}

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

void	add_to_env(t_program_data *pd, char *variable)
{
	char	**new_env;
	int		new_env_size;
	int		current_env_var;

	current_env_var = 0;
	new_env_size = pd->amount_env_lines + 2;
	new_env = ft_malloc(new_env_size * sizeof(char *));
	while (pd->env[current_env_var] != NULL)
	{
		new_env[current_env_var] = pd->env[current_env_var];
		current_env_var++;
	}
	new_env[current_env_var] = ft_strdup(variable);
	new_env[current_env_var + 1] = NULL;
	free(pd->env);
	pd->env = new_env;
	pd->amount_env_lines = current_env_var + 1;
}

void	remove_from_env(t_program_data *pd, char *str)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (pd->env[i] && ft_strncmp(str, pd->env[i], len))
		i++;
	if (!pd->env[i])
		return ;
	free(pd->env[i]);
	if (i != pd->amount_env_lines)
		pd->env[i] = pd->env[pd->amount_env_lines - 1];
	pd->env[pd->amount_env_lines - 1] = 0;
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
