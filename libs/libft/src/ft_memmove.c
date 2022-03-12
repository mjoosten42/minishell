/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:50:29 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 15:59:28 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t len)
{
	char	*d;
	char	*s;

	d = dest;
	s = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (d < s)
		ft_memcpy(d, s, len);
	else
	{
		s = src + (len - 1);
		d = dest + (len - 1);
		while (len > 0)
		{
			*d = *s;
			d--;
			s--;
			len--;
		}
	}
	return (dest);
}
