/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjoosten <mjoosten@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 14:57:34 by mjoosten      #+#    #+#                 */
/*   Updated: 2022/03/21 15:04:12 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

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

int	main(void)
{
	t_token	*head;
	char	*str;

	//signal(SIGINT, ft_signal);
	//signal(SIGQUIT, ft_signal);
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
		ft_parse(head);
		free(str);
	}
	ft_putstr("exit\n");
	exit(EXIT_SUCCESS);
}
