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

	token = *head;
	if (token)
	{
		while (token->next)
			token = token->next;
		token->next = new_token;
		new_token->prev = token;
	}
	else
		*head = new_token;
}

t_token	*token_new(void)
{
	t_token		*token;
	static int	i;

	token = ft_malloc(sizeof(t_token));
	token->position = i++;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

char	*get_token_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	printf("Str: %s\n", str);
	while (ft_strchr(WORD_END, str[i]))
		i++;
	printf("Str: %s\nI: %d\n", str, i);
	value = ft_malloc(i + 1);
	ft_strlcpy(value, str, i + 1);
	return (value);
}

t_token	*word_token(char *str)
{
	t_token	*token;

	token = token_new();
	token->value = get_token_value(str);
	printf("%s - token val\n", token->value);
	return (token);
}

t_token	*special_char_token(char *str)
{
	t_token	*token;
	char	c;

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
	token->value = get_token_value(str);
	return (token);
}

void	print_tokens(t_token *token)
{
	printf("- id - type - value -\n");
	while (token)
	{
		printf("|  %2i |  %i   | %s\n", token->position, token->type, token->value);
		token = token->next;
	}
}

void	lexer(char *str)
{
	t_token	*head;
	char	*start;
	int		i;
	int		in_word;

	i = 0;
	head = 0;
	in_word = 0;
	while (str[i] != '\0')
	{
		if (in_word == 0 && ft_isalpha(str[i]))
		{
			printf("In word %c\n", str[i]);
			start = str + i;
			in_word = 1;
		}
		//if (ft_strchr(SPECIAL_CHARS, str[i]))
		//	token_add_back(&head, special_char_token(str + i));
		if (in_word == 1 && !ft_isalpha(str[i]))
		{
			token_add_back(&head, word_token(start));
			in_word = 0;
		}
		i++;
	}
	print_tokens(head);
}
