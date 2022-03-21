#include "minishell.h"
#include "libft.h"

void	ft_parse_word(t_token **head);
void	ft_parse_quote(t_token **head);
void	ft_remove_token(t_token **head);

void	ft_parse(t_token *head)
{
	t_token	*ptr;

	ptr = head;
	while (ptr)
	{
		print_tokens(head);
		if (ptr->type == space)
			ft_remove_token(&ptr);
		ptr = ptr->next;
	}
	while (head)
	{
		print_tokens(head);
		if (head->type == word)
			ft_parse_word(&head);
		if (head->type == quote)
			ft_parse_quote(&head);
		head = head->next;
	}
}

void	ft_remove_token(t_token **head)
{
	t_token	*prev;
	t_token	*next;

	prev = head[0]->prev;
	next = head[0]->next;
	free(head[0]->value);
	free(head[0]);
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
	int		i;
	int		j;

	i = 1;
	ptr = *head;
	while (ptr->next && ptr->next->type == word)
	{
		ptr = ptr->next;
		i++;
	}
	*head = ptr->next;
	strs = ft_calloc(i + 1, (sizeof(void *)));
	j = 0;
	while (i--)
	{
		strs[i] = ptr->value;
		ptr = ptr->prev;
	}
	if (!fork())
		if (execve(ft_getpath(*strs), strs, 0) < 0)
			ft_error(NULL);
	wait(0);
}
