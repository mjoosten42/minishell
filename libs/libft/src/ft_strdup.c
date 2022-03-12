/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:50:45 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 15:57:45 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*string;

	string = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (string == NULL)
		return (NULL);
	ft_strlcpy(string, s1, ft_strlen(s1) + 1);
	return (string);
}
