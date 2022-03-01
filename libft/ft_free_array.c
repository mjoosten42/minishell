/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:51:28 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/01 13:56:57 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(void *array)
{
	void	**start;
	void	**arr;

	if (!array)
		return ;
	arr = array;
	start = arr;
	while (*arr)
		free(*arr++);
	free(start);
}
