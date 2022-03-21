#include "minishell.h"
#include "libft.h"

void	ft_parse_word(t_token **head);
void	ft_parse_quote(t_token **head);
void	ft_remove_token(t_token *head);
void	ft_spaces(t_token **head);

void	ft_parse(t_token *head)
{
	print_tokens(head);
	ft_spaces(&head);
	print_tokens(head);
	while (head)
	{
		if (head->type == word)
			ft_parse_word(&head);
		else if (head->type == quote)
			ft_parse_quote(&head);
		else
			head = head->next;
	}
}

void	ft_spaces(t_token **head)
{
	t_token	*ptr;
	int		in_quote;
	int		in_dquote;

	in_dquote = 0;
	in_quote = 0;
	ptr = *head;
	while (ptr)
	{
		if (ptr->type == quote)
			in_quote = !in_quote;
		if (ptr->type == dquote)
			in_dquote = !in_dquote;
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

void	ft_parse_quote(t_token **head)
{
	(void)head;
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
