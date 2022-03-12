/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rubennijhuis <rubennijhuis@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/12 15:50:42 by rubennijhui   #+#    #+#                 */
/*   Updated: 2022/03/12 16:04:27 by rubennijhui   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_everything(char ***string, unsigned int word_amount)
{
	while (word_amount > 0)
	{
		--word_amount;
		free((*string)[word_amount]);
	}
	free((*string));
	(*string) = NULL;
}

static unsigned int	word_len(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s != c && *s != 0)
	{
		s++;
		i++;
	}
	return (i);
}

static unsigned int	get_amount_of_words(char const *s, char c)
{
	unsigned int	amount_words;
	unsigned int	new_word;
	unsigned int	i;

	amount_words = 0;
	new_word = 0;
	i = 0;
	while (*s != 0)
	{
		if (new_word == 0 && *s != c)
		{
			amount_words++;
			new_word = !new_word;
		}
		if (*s == c)
			new_word = 0;
		i++;
		s++;
	}
	return (amount_words);
}

static void	add_words_to_string(const char *s, char c, char ***string)
{
	unsigned int	new_word;
	unsigned int	n_words;
	unsigned int	word_length;

	new_word = 0;
	n_words = 0;
	while (*s != 0)
	{
		if (new_word == 0 && *s != c)
		{
			new_word = !new_word;
			(*string)[n_words] = ft_calloc((word_len(s, c) + 1), sizeof(char));
			if ((*string)[n_words] == NULL)
			{
				free_everything(string, n_words);
				return ;
			}
			ft_strlcpy((*string)[n_words], s, word_len(s, c) + 1);
			n_words++;
			word_length = 0;
		}
		if (*s == c)
			new_word = 0;
		s++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**string;
	unsigned int	amount_of_words;

	if (s == NULL)
		return (NULL);
	amount_of_words = get_amount_of_words(s, c);
	string = ft_calloc((amount_of_words + 1), sizeof(char *));
	if (string == NULL)
		return (NULL);
	string[amount_of_words] = NULL;
	add_words_to_string(s, c, &string);
	return (string);
}
