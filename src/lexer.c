#include "minishell.h"
#include "libft.h"

t_token	*special_char_token(char *str);
t_token	*word_token(char *str);
int		dollar_len(char *str);

void	ft_lexer(t_token *head, char *str)
{
	t_token	*new;

	while (*str)
	{
		if (ft_strchr(META_CHARS, *str))
			new = special_char_token(str);
		else
			new = word_token(str);
		str += token_add_back(head, new);
	}
}

t_token	*special_char_token(char *str)
{
	t_token	*token;
	int		type;
	int		len;

	len = 1;
	token = ft_malloc(sizeof(t_token));
	type = ft_strchr(META_CHARS, str[0]) - META_CHARS;
	if (type == space || type == tab)
		while (str[len] == ' ' || str[len] == '\t')
			len++;
	if (type == dollar)
		len += dollar_len(&str[1]);
	if ((type == red_in && str[1] == '<') || (type == red_out && str[1] == '>'))
	{
		len++;
		if (type == red_in)
			type = heredoc;
		else
			type = red_out_app;
	}
	token->type = type;
	token->value = ft_substr(str, 0, len);
	return (token);
}

t_token	*word_token(char *str)
{
	t_token	*token;
	int		i;

	i = 0;
	token = ft_malloc(sizeof(t_token));
	token->type = word;
	while (!ft_strchr(META_CHARS, str[i]))
		i++;
	token->value = ft_substr(str, 0, i);
	return (token);
}

int	dollar_len(char *str)
{
	if (*str == '?')
		return (1);
	return (export_name_len(str));
}
