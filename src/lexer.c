#include "minishell.h"
#include "libft.h"

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
		new_token->position = i;
	}
	else
		*head = new_token;
	return (ft_strlen(new_token->value));
}

t_token	*token_new(void)
{
	t_token		*token;

	token = ft_malloc(sizeof(t_token));
	ft_memset(token, 0, sizeof(t_token));
	return (token);
}

char	*ft_strndup(char *str, int len)
{
	char	*dup;

	dup = ft_malloc(len + 1);
	ft_strlcpy(dup, str, len + 1);
	return (dup);
}

t_token	*word_token(char *str)
{
	t_token	*token;
	int		i;

	i = 0;
	token = token_new();
	token->type = word;
	while (!ft_strchr(META_CHARS, str[i]))
		i++;
	token->value = ft_strndup(str, i);
	return (token);
}

int	get_space_len(char *str)
{
	int	len;

	len = 0;
	while (*str && str[len] == ' ')
		len++;
	return (len);
}

	//	Find metachar position in META_CHARS,
	//	and subtract it from META_CHARS itself to get type
t_token	*special_char_token(char *str)
{
	t_token	*token;
	int		len;

	len = 1;
	token = token_new();
	token->type = ft_strchr(META_CHARS, str[0]) - META_CHARS;
	if (token->type == space)
		len = get_space_len(str);
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
	token->value = ft_strndup(str, len);
	return (token);
}

void	lexer(t_token **head, char *str)
{
	int	i;

	if (!*str)
		return ;
	if (ft_strchr(META_CHARS, *str))
		i = token_add_back(head, special_char_token(str));
	else if (ft_isprint(*str))
		i = token_add_back(head, word_token(str));
	else
		i = 1;
	lexer(head, str + i);
}
