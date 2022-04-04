#include "minishell.h"
#include "libft.h"

t_token	*token_start(void)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	token->position = 0;
	token->next = NULL;
	token->prev = NULL;
	token->value = NULL;
	token->type = start;
	return (token);
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

void	ft_remove_token(t_token *token)
{
	if (!token)
		return ;
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free(token->value);
	free(token);
}

#include <stdio.h>

void	print_tokens(t_token *token)
{
	char	*types[] = {
		"pipe_char",
		"red_in",
		"red_out",
		"dollar",
		"dquote",
		"quote",
		"space",
		"tab",
		"newline",
		"here_doc",
		"red_out_app",
		"word",
		"start"
	};

	printf(" - id ------------ type - value\n");
	while (token)
	{
		printf(" | %2i | %15s | [%s]\n",
			token->position, types[token->type], token->value);
		token = token->next;
	}
	printf("\n");
}
