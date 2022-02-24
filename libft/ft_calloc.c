/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:20:26 by mjoosten          #+#    #+#             */
/*   Updated: 2021/12/06 16:26:19 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		len;
	void	*ret;

	len = count * size;
	ret = malloc(len);
	if (!ret)
		return (0);
	ft_bzero(ret, len);
	return (ret);
}
