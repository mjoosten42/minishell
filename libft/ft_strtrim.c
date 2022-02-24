/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:22:20 by mjoosten          #+#    #+#             */
/*   Updated: 2021/12/06 17:28:57 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (0);
	while (*s1 && ft_strchr((char *)set, *(char *)s1))
		s1++;
	len = ft_strlen(s1);
	while (ft_strchr((char *)set, *((char *)s1 + len - 1)))
		len--;
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, len + 1);
	return (str);
}
