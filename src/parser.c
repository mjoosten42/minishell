#include "minishell.h"
#include "libft.h"

void	ft_expand(t_token **head);
void	ft_parse_word(t_token *token);
void	ft_expand_dollar(t_token *token);
void	ft_expand_quotes(t_token *token, enum e_symbol type);
void	ft_remove_token(t_token *head);

void	ft_parse(t_token **head)
{
	t_token	*ptr;

	print_tokens(*head);
	ft_expand(head);
	print_tokens(*head);
	ptr = *head;
	while (ptr)
	{
		if (ptr->type == word)
		{
			ft_parse_word(ptr);
			return ;
		}
		ptr = ptr->next;
	}
}

void	ft_expand(t_token **head)
{
	t_token	*ptr;
	t_token	*next;

	ptr = *head;
	while (ptr)
	{
		if (ptr->type == quote)
			ft_expand_quotes(ptr, quote);
		else if (ptr->type == dquote)
			ft_expand_quotes(ptr, dquote);
		else if (ptr->type == dollar)
			ft_expand_dollar(ptr);
		else if (ptr->type == space)
		{
			next = ptr->next;
			ft_remove_token(ptr);
			if (ptr == *head)
				*head = next;
			ptr = next;
		}
		else
			ptr = ptr->next;
	}
}

void	ft_expand_dollar(t_token *token)
{
	token->type = word;
	free(token->value);
	if (token->next && token->next->type == word)
	{
		token->value = ft_strdup("[TODO: get from env]");
		ft_remove_token(token->next);
	}
	else
		token->value = ft_strdup("$");
}

/**
 * if input has qoutes go through list to match qoutes
 * merge value of block in between qoutes
 * 
 * remove blocks
 * 
 * Edit: set first (d)quote to empty string with type word
 * then keep joining until (d)quote is reached.
 */
void	ft_expand_quotes(t_token *token, enum e_symbol type)
{
	char	*tmp;

	token->type = word;
	free(token->value);
	token->value = ft_strdup("");
	if (!token->next)
		ft_error("Error: solo (d)quote");
	while (token->next->type != type)
	{
		if (type == dquote && token->next->type == dollar)
			ft_expand_dollar(token->next);
		tmp = token->value;
		token->value = ft_strjoin(token->value, token->next->value);
		free(tmp);
		ft_remove_token(token->next);
		if (!token->next)
			ft_error("Error: solo (d)quote");
	}
	ft_remove_token(token->next);
}

void	ft_parse_word(t_token *token)
{
	extern char	**environ;
	t_token		*ptr;
	char		**strs;
	char		*path;
	int			i;

	i = 1;
	ptr = token;
	while (ptr->next && ptr->next->type == word)
	{
		ptr = ptr->next;
		i++;
	}
	strs = ft_calloc(i + 1, (sizeof(void *)));
	while (i--)
	{
		strs[i] = ptr->value;
		ptr = ptr->prev;
	}
	path = ft_getpath(*strs);
	if (!path)
		return ;
	if (!fork())
		if (execve(path, strs, environ) < 0)
			ft_error(NULL);
	wait(0);
	ft_free_array(strs);
	free(path);
}

void	ft_remove_token(t_token *token)
{
	t_token	*prev;
	t_token	*next;

	if (!token)
		return ;
	prev = token->prev;
	next = token->next;
	free(token->value);
	free(token);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}
