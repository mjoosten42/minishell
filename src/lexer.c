#include "libft.h"
#include "minishell.h"

#define SPECIAL_CHARS "\"\'><|$"
#define WORD_END "\t \"\'><|$"

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

char	*get_token_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	while (!ft_strchr(WORD_END, str[i]))
		i++;
	value = ft_malloc(i + 1);
	ft_strlcpy(value, str, i + 1);
	return (value);
}

t_token	*word_token(char *str)
{
	t_token	*token;

	token = token_new();
	token->value = get_token_value(str);
	return (token);
}

t_token	*special_char_token(char *str)
{
	t_token	*token;
	char	*new;
	char	c;
	int		len;

	len = 1;
	c = *str;
	token = token_new();
	if (c == '\'')
		token->type = quote;
	if (c == '\"')
		token->type = dquote;
	if (c == '>')
	{
		if (str[1] == '>')
		{
			len++;
			token->type = red_out_app;
		}
		else
			token->type = red_out;
	}
	if (c == '<')
	{
		if (str[1] == '<')
		{
			len++;
			token->type = here_doc;
		}
		else
			token->type = red_in;
	}
	if (c == '|')
		token->type = pipe_char;
	if (c == '$')
		token->type = dollar;
	new = ft_malloc(len + 1);
	ft_strlcpy(new, str, len + 1);
	token->value = new;
	return (token);
}

void	print_tokens(t_token *token)
{
	printf("\n- id - type - value -\n");
	while (token)
	{
		printf("|  %2i |  %i   | %s\n", token->position, token->type, token->value);
		token = token->next;
	}
	printf("\n");
}

int	ft_isword(int c)
{
	if (ft_isalpha(c))
		return (1);
	if (c == '-')
		return (1);
	return (0);
}

void	lexer(t_token **head, char *str)
{
	int	i;

	if (!*str)
		return ;
	if (ft_isword(*str))
		i = token_add_back(head, word_token(str));
	else if (ft_strchr(SPECIAL_CHARS, *str))
		i = token_add_back(head, special_char_token(str));
	else
		i = 1;
	lexer(head, str + i);
}

void	get_tokens(char *str)
{
	t_token	*head;

	lexer(&head, str);
	print_tokens(head);
}
