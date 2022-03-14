/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:21:22 by mjoosten          #+#    #+#             */
/*   Updated: 2021/12/06 16:36:01 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!(dst || src))
		return (0);
	if (dst > src && dst < src + len)
		while (len--)
			*((char *)dst + len) = *((char *)src + len);
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
