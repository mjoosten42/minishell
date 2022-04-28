/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:09:23 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/26 10:23:42 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	echo(char **strs)
{
	int		nl;
	int		i;

	if (!strs[1])
		return (ft_putchar_fd('\n', 1));
	i = 1;
	nl = ft_strncmp(strs[1], "-n", 3);
	if (!nl)
		i++;
	while (!ft_strncmp(strs[i], "-n", 3))
		i++;
	while (strs[i])
	{
		ft_putstr(strs[i]);
		if (strs[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (nl)
		ft_putchar('\n');
}
