/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:46:06 by mjoosten          #+#    #+#             */
/*   Updated: 2022/01/24 16:29:57 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(int nbr, char *base)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(base);
	if (nbr / size)
		i = ft_putnbr_base(nbr / size, base);
	else if (nbr < 0)
		i += ft_putchar('-');
	if (nbr > 0)
		return (i + ft_putchar(base[nbr % size]));
	return (i + ft_putchar(base[-nbr % size]));
}
