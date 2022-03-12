/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:20:45 by mjoosten          #+#    #+#             */
/*   Updated: 2021/12/06 16:26:27 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recitoa(int n, char *str);

char	*ft_itoa(int n)
{
	char	*str;
	int		min;
	int		m;
	int		i;

	min = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0 && ++min)
		n = -n;
	m = n;
	i = 0;
	while (m >= 10 && ++i)
		m /= 10;
	str = malloc(sizeof(*str) * (i + min + 2));
	if (!str)
		return (0);
	*(str + i + min + 1) = 0;
	if (min)
		*str = '-';
	ft_recitoa(n, str + i + min);
	return (str);
}

static void	ft_recitoa(int n, char *str)
{
	if (n >= 10)
		ft_recitoa(n / 10, str - 1);
	*str = '0' + n % 10;
}
