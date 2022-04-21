/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:09:40 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:09:44 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int				is_all_digits(char *str);
unsigned char	ft_char_atoi(char *str);

void	ft_exit(char **strs)
{
	t_program_data	*pd;

	pd = pd_get();
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (!strs[1])
		exit(WEXITSTATUS(pd->last_exit_status));
	if (!is_all_digits(strs[1]) || ft_strlen(strs[1]) > 19)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(strs[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		pd->last_exit_status = 1;
		exit(255);
	}
	else if (strs[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		pd->last_exit_status = 1;
	}
	else
		exit(ft_char_atoi(strs[1]));
}

int	is_all_digits(char *str)
{
	int	strlen;
	int	i;

	if (*str == '-')
		str++;
	strlen = ft_strlen(str);
	i = 0;
	while (i < strlen)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

unsigned char	ft_char_atoi(char *str)
{
	unsigned char	number;
	int				min;

	min = 0;
	number = 0;
	if (*str == '-')
	{
		str++;
		min = 1;
	}
	while (*str == '0' && str[1])
		str++;
	while (*str)
		number = 10 * number + *str++ - '0';
	if (min)
		number = 256 - number;
	return (number);
}
