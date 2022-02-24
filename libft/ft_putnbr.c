/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:39:24 by mjoosten          #+#    #+#             */
/*   Updated: 2022/01/24 16:29:31 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	char	c;
	int		i;

	i = 0;
	if (n / 10)
		i = ft_putnbr(n / 10);
	else if (n < 0)
		i += ft_putchar('-');
	if (n > 0)
		c = '0' + n % 10;
	else
		c = '0' - (n % 10);
	return (i + ft_putchar(c));
}
