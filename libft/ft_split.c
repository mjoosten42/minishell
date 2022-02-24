/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:21:43 by mjoosten          #+#    #+#             */
/*   Updated: 2021/12/06 16:27:15 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c);
static int	ft_wordlength(char const *s, char c);
static int	ft_wordcpy(char **strs, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (0);
	if (!c)
	{
		strs = malloc(1);
		*strs = 0;
		return (strs);
	}
	while (*s == c)
		s++;
	strs = malloc(sizeof(*strs) * (ft_wordcount(s, c) + 1));
	if (!strs)
		return (0);
	if (ft_wordcpy(strs, s, c))
		return (0);
	*(strs + ft_wordcount(s, c)) = 0;
	return (strs);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		while (*s == c)
			s++;
		i++;
	}
	return (i);
}

static int	ft_wordlength(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_wordcpy(char **strs, char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	while (*s)
	{
		len = ft_wordlength(s, c);
		strs[i] = malloc(sizeof(*strs[i]) * len + 1);
		if (!strs[i])
		{
			ft_free_array((void **)strs);
			return (1);
		}
		ft_strlcpy(strs[i], s, len + 1);
		s += len;
		while (*s == c)
			s++;
		i++;
	}
	return (0);
}
