#include "minishell.h"
#include "libft.h"

int		token_add_back(t_token *token, t_token *new_token);
t_token	*special_char_token(char *str);
t_token	*word_token(char *str);

void	lexer(t_token *head, char *str)
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

int	token_add_back(t_token *token, t_token *new_token)
{
	int	i;

	i = 1;
	while (token->next)
	{
		i++;
		token = token->next;
	}
	token->next = new_token;
	new_token->prev = token;
	new_token->next = NULL;
	new_token->position = i;
	return (ft_strlen(new_token->value));
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
