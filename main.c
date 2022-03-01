/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/01 13:44:11 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			break ;
		if (!*str)
			continue ;
		add_history(str);
		ft_execute(str);
		free(str);
	}
	ft_putchar_fd(BACKSPACE, 0);
	ft_putchar_fd(BACKSPACE, 0);
	ft_putstr("exit\n");
	exit(EXIT_SUCCESS);
}

void	ft_print_error(char *str)
{
	rl_line_buffer[ft_strlen(rl_line_buffer) - 1] = 0;
	ft_putstr_fd(rl_line_buffer, 2);
	ft_putstr_fd(str, 2);
}
