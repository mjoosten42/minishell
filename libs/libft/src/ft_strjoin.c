/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:50:48 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 15:57:59 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	strlen1;
	size_t	strlen2;

	if (!s1 || !s2)
		return (NULL);
	strlen1 = ft_strlen(s1);
	strlen2 = ft_strlen(s2);
	string = ft_calloc((strlen1 + strlen2 + 1), sizeof(char));
	if (string == NULL)
		return (NULL);
	ft_strlcpy(string, s1, strlen1 + 1);
	ft_strlcpy(string + strlen1, s2, strlen2 + 1);
	return (string);
}
