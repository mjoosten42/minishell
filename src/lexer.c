#include "libft.h"
#include "minishell.h"

#define SPECIAL_CHARS "\"\'><|$"
#define WORD_END "\t \"\'><|$"

/**
 * ls
 * start
 * 	empty_token_list
 * 
 * get first token
 * token is a word/cmd (example)
 * 
 * first token != SPECIAL_CHARS
 * 
 * 
 */

void	token_add_back(t_token **head, t_token *new_token)
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

	len = 0;
	c = *str;
	token = token_new();
	if (c == '\'')
		token->type = quote;
	if (c == '\"')
		token->type = dquote;
	if (c == '>')
		token->type = red_out;
	if (c == '<')
		token->type = red_in;
	if (c == '|')
		token->type = pipe_char;
	if (c == '$')
		token->type = dollar;
	while (ft_strchr(SPECIAL_CHARS, str[len]))
		len++;
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
}

void	lexer(char *str)
{
	t_token	*head;
	int		i;
	int		in_word;

	i = 0;
	head = 0;
	in_word = 0;
	while (str[i] != '\0')
	{
		if (in_word == 0 && ft_isalpha(str[i]))
		{
			token_add_back(&head, word_token(str + i));
			in_word = 1;
		}
		if (in_word == 1 && !ft_isalpha(str[i]))
			in_word = 0;
		if (ft_strchr(SPECIAL_CHARS, str[i]))
			token_add_back(&head, special_char_token(str + i));
		i++;
	}
	print_tokens(head);
}
