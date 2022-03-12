/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:50:31 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 15:59:28 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int val, size_t len)
{
	unsigned char	*ptr_dest;

	ptr_dest = dest;
	while (len > 0)
	{
		*ptr_dest = val;
		ptr_dest++;
		len--;
	}
	return (dest);
}
