/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:51:01 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 15:57:54 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	contains(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *src, char const *set)
{
	char			*string;
	const char		*end;
	size_t			len;

	if (src == NULL)
		return (NULL);
	while (contains(*src, set))
		++src;
	if (*src == '\0')
		return (ft_strdup(""));
	end = ft_strchr(src, 0) - 1;
	while (contains(*end, set))
		--end;
	len = end - src + 1;
	string = ft_calloc((len + 1), sizeof(char));
	if (string == NULL)
		return (NULL);
	ft_strlcpy(string, src, len + 1);
	return (string);
}
