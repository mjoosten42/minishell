/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/01 11:50:29 by mjoosten         ###   ########.fr       */
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

void	ft_error(char *str)
{
	if (str)
		ft_putendl_fd(str, 2);
	else
		perror(0);
	exit(EXIT_FAILURE);
}

void	ft_print_error(char *str)
{
	rl_line_buffer[ft_strlen(rl_line_buffer) - 1] = 0;
	ft_putstr_fd(rl_line_buffer, 2);
	ft_putstr_fd(str, 2);
}

void	ft_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		ft_putendl_fd(environ[i++], 1);
}
