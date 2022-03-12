/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:49:49 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 15:58:16 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	overflow_check(const char *str, int sign)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		++i;
	if (i >= 20 && sign == -1)
		return (0);
	else if (i >= 20 && sign == 1)
		return (-1);
	return (2);
}

static int	contains(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	ft_atoi(const char *src)
{
	int				sign;
	long			val;
	unsigned int	i;

	sign = 1;
	val = 0;
	i = 0;
	while (contains("\t\n\v\f\r ", src[i]))
		i++;
	if (src[i] == '+' || src[i] == '-')
	{
		if (src[i] == '-')
			sign = -1;
		i++;
	}
	if (overflow_check(&src[i], sign) < 2)
		return (overflow_check(&src[i], sign));
	while (ft_isdigit(src[i]))
	{
		val *= 10;
		val += src[i] - '0';
		i++;
	}
	return ((int) val * sign);
}
