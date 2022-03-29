#include "minishell.h"
#include "libft.h"

int		token_add_back(t_token **head, t_token *new_token);
t_token	*special_char_token(char *str);
t_token	*word_token(char *str);

void	lexer(t_token **head, char *str)
{
	while (*str)
	{
		if (ft_strchr(META_CHARS, *str))
			str += token_add_back(head, special_char_token(str));
		else if (ft_isprint(*str))
			str += token_add_back(head, word_token(str));
		else
			str++;
	}
}

int	token_add_back(t_token **head, t_token *new_token)
{
	t_token	*token;
	int		i;

	i = 1;
	token = *head;
	if (token)
	{
		while (token->next)
		{
			i++;
			token = token->next;
		}
		token->next = new_token;
		new_token->prev = token;
		new_token->next = NULL;
		new_token->position = i;
	}
	else
	{
		*head = new_token;
		new_token->prev = NULL;
		new_token->next = NULL;
		new_token->position = 0;
	}
	return (ft_strlen(new_token->value));
}

	//	Find metachar position in META_CHARS,
	//	and subtract it from META_CHARS itself to get type
t_token	*special_char_token(char *str)
{
	t_token	*token;
	int		len;

	len = 1;
	token = ft_malloc(sizeof(t_token));
	token->type = ft_strchr(META_CHARS, str[0]) - META_CHARS;
	if (token->type == space)
		while (*str && str[len] == ' ')
			len++;
	else if (token->type == red_in && str[1] == '<')
	{
		token->type = here_doc;
		len++;
	}
	else if (token->type == red_out && str[1] == '>')
	{
		token->type = red_out_app;
		len++;
	}
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
