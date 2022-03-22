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
	token->position = 0;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

char	*ft_strndup(char *str, int len)
{
	char	*dup;

	dup = malloc(len + 1);
	ft_strlcpy(dup, str, len + 1);
	return (dup);
}

char	*get_token_value(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr(META_CHARS, str[i]))
		i++;
	return (ft_strndup(str, i));
}

t_token	*word_token(char *str)
{
	t_token	*token;

	token = token_new();
	token->type = word;
	token->value = get_token_value(str);
	return (token);
}

t_token	*special_char_token(char *str)
{
	t_token	*token;
	char	c;
	int		len;

	len = 1;
	c = *str;
	token = token_new();
	if (c == '|')
		token->type = pipe_char;
	else if (c == ' ')
		token->type = space;
	else if (c == '<')
	{
		if (str[1] == '<')
		{
			len++;
			token->type = here_doc;
		}
		else
			token->type = red_in;
	}
	else if (c == '>')
	{
		if (str[1] == '>')
		{
			len++;
			token->type = red_out_app;
		}
		else
			token->type = red_out;
	}
	else if (c == '$')
		token->type = dollar;
	else if (c == '\"')
		token->type = dquote;
	else if (c == '\'')
		token->type = quote;
	else if (c == ' ')
		token->type = space;
	else if (c == '\t')
		token->type = tab;
	else if (c == '\n')
		token->type = newline;
	token->value = ft_strndup(str, len);
	return (token);
}

char	*get_space_value(char *str)
{
	char	*spaces;
	int		len;

	len = 0;
	while (*str && str[len] == ' ')
		len++;
	spaces = ft_strndup(str, len);
	return (spaces);
}

t_token	*space_token(char *str)
{
	t_token	*token;

	token = token_new();
	token->type = space;
	token->value = get_space_value(str);
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
