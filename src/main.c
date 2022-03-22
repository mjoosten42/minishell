/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjoosten <mjoosten@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 14:57:34 by mjoosten      #+#    #+#                 */
/*   Updated: 2022/03/22 15:38:27 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <sys/ioctl.h>
#include <termios.h>

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
		new_env[current_env_var] = ft_strdup(pd->env[current_env_var]);
		current_env_var++;
	}
	new_env[current_env_var] = variable;
	new_env[current_env_var + 1] = NULL;
	ft_free_array(pd->env);
	pd->env = new_env;
	pd->amount_env_lines = current_env_var + 2;
}

void	remove_from_env(t_program_data *pd, char *variable)
{
	int		current_line;
	int		var_length;
	char	*temp_pointer;

	current_line = 0;
	var_length = ft_strlen(variable);
	while (current_line < pd->amount_env_lines)
	{
		if (ft_strncmp(variable, pd->env[current_line], var_length))
			break ;
		current_line++;
	}
	temp_pointer = 
	*a = *b;
	*b = temp;
}

int	main(int argc, char *argv[], char *env[])
{
	// char			*str;
	// t_token			*head;
	(void)argc;
	(void)argv;
	t_program_data	program_data;

	copy_env(&program_data, env);
	add_to_env(&program_data, "RUBEN=cool");
	print_env(program_data.env);
	//signal(SIGINT, ft_signal);
	//signal(SIGQUIT, ft_signal);
	// while (1)
	// {
	// 	head = 0;
	// 	str = readline("minishell$ ");
	// 	if (!str)
	// 		break ;
	// 	if (!*str)
	// 	{
	// 		free(str);
	// 		continue ;
	// 	}
	// 	add_history(str);
	// 	lexer(&head, str);
	// 	ft_parse(&head);
	// 	free(str);
	// }
	// ft_putstr("exit\n");
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
