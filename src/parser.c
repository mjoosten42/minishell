#include "minishell.h"
#include "libft.h"

void	ft_parse_word(t_token **head);
void	ft_expand_quotes(t_token **head);
void	ft_parse_quote(t_token **head, enum e_symbol type);
void	ft_remove_token(t_token *head);
void	ft_expand(t_token **head);

void	ft_parse(t_token **head)
{
	t_token	*ptr;

	print_tokens(*head);
	ft_expand(head);
	ft_expand_quotes(head);
	ptr = *head;
	while (ptr)
	{
		if (ptr->type == word)
		{
			ft_parse_word(&ptr);
			continue ;
		}
		ptr = ptr->next;
	}
}

void	ft_expand_dollar(t_token *ptr)
{
	if (ptr->next->type == word)
		return ;
}

void	ft_expand(t_token **head)
{
	t_token	*ptr;
	int		in_quote;
	int		in_dquote;

	in_dquote = 0;
	in_quote = 0;
	ptr = *head;
	while (ptr)
	{
		if (ptr->type == quote && !in_dquote)
			in_quote = !in_quote;
		if (ptr->type == dquote && !in_quote)
			in_dquote = !in_dquote;
		if (ptr->type == dollar && !in_quote)
			ft_expand_dollar(ptr);
		if (ptr->type == space && !(in_quote || in_dquote))
			ft_remove_token(ptr);
		ptr = ptr->next;
	}
}

void	ft_remove_token(t_token *head)
{
	t_token	*prev;
	t_token	*next;

	prev = head->prev;
	next = head->next;
	free(head->value);
	free(head);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}

void	ft_expand_quotes(t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (ptr->type == dquote)
		{
			ft_parse_quote(&ptr, dquote);
			ptr = *head;
		}
		if (ptr->type == quote)
		{
			ft_parse_quote(&ptr, quote);
			ptr = *head;
		}
		ptr = ptr->next;
	}
}

/**
 * if input has qoutes go through list to match qoutes
 * merge value of block in between qoutes
 * 
 * remove blocks
 */
void	ft_parse_quote(t_token **head, enum e_symbol type)
{
	t_token	*ptr;
	t_token	*next_block_ptr;
	t_token	*first_block;
	char	*total_value;

	ptr = head[0]->next;
	ft_remove_token(*head);
	if (!ptr)
		return ;
	total_value = ptr->value;
	first_block = ptr;
	ptr->type = word;
	ptr = ptr->next;
	while (ptr && ptr->type != type)
	{
		total_value = ft_strjoin(total_value, ptr->value);
		next_block_ptr = ptr->next;
		ft_remove_token(ptr);
		ptr = ptr->next;
	}
	if (!ptr)
		return ;
	ft_remove_token(ptr);
	free(first_block->value);
	first_block->value = total_value;
}

void	ft_parse_word(t_token **head)
{
	t_token	*ptr;
	char	**strs;
	char	*path;
	int		i;

	i = 1;
	ptr = *head;
	while (ptr->next && ptr->next->type == word)
	{
		ptr = ptr->next;
		i++;
	}
	*head = ptr->next;
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
		if (execve(path, strs, 0) < 0)
			ft_error(NULL);
	wait(0);
	free(path);
	ft_free_array(strs);
}
