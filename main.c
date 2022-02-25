/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/25 15:53:49 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			ft_eof();
		if (!*str)
			continue ;
		add_history(str);
		ft_execute(str);
		free(str);
	}
}

void	ft_eof(void)
{
	char	str[8];

	str[0] = BACKSPACE;
	str[1] = BACKSPACE;
	ft_strlcat(str, "exit\n", 8);
	ft_putstr_fd(str, 0);
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
