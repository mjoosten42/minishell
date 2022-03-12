/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:50:26 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 15:59:29 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*one;
	const unsigned char	*two;

	one = s1;
	two = s2;
	while (n != 0)
	{
		if (*one != *two)
			return (*one - *two);
		n--;
		one++;
		two++;
	}
	return (0);
}
