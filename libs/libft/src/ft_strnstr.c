/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:50:58 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 15:59:07 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	l;

	l = *h;
	if (*n == '\0')
		return ((char *)h);
	l = ft_strlen(n);
	while (len >= l)
	{
		len--;
		if (ft_strncmp(h, n, l) == 0)
			return ((char *)h);
		h++;
	}
	return (NULL);
}
