/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:21:49 by mjoosten          #+#    #+#             */
/*   Updated: 2021/12/06 16:27:20 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	s2 = malloc(sizeof(*s2) * len + 1);
	if (!s2)
		return (0);
	ft_strlcpy(s2, s1, len + 1);
	return (s2);
}
