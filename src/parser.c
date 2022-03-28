#include "minishell.h"
#include "libft.h"
#include "fcntl.h"

void	ft_expand(t_token **head);
void	ft_expand_dollar(t_token *token);
void	ft_expand_quotes(t_token *token, enum e_symbol type);
void	ft_remove_token(t_token *head);
void	ft_get_fd0(t_token **head, int *fd0);
int		ft_get_fd1(t_token **head, int *fd1);
char	**ft_get_args(t_token **head);

void	ft_parse(t_token **head, int pipefd)
{
	pid_t	pid;
	char	**strs;
	int		fds[2];
	int		pipe_read;
	int		exit_status;

	fds[0] = pipefd;
	fds[1] = 1;
	ft_get_fd0(head, &fds[0]);
	pipe_read = ft_get_fd1(head, &fds[1]);
	strs = ft_get_args(head);
	ft_getpath(strs);
	if (!*strs)
		return ;
	pid = ft_exec(strs, fds);
	ft_free_array(strs);
	if (pipe_read)
	{
		ft_parse(&(*head)->next, pipe_read);
		ft_remove_token(*head);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		g_pd.last_exit_status = WEXITSTATUS(exit_status);
	}
}

void	ft_get_fd0(t_token **head, int *fd0)
{
	t_token	*token;

	token = *head;
	while (token && token->type != pipe_char)
	{
		if (token->type == red_in && token->next->type == word)
		{
			*fd0 = open(token->next->value, O_RDONLY);
			if (*fd0 < 0)
				perror(token->next->value);
			if (token == *head)
				*head = token->next->next;
			ft_remove_token(token);
			ft_remove_token(token->next);
		}
		token = token->next;
	}
}

//	Look for > and >> tokens, get fd with open() and remove the token.
//	If followed by a pipe, make a pipe and return the read end.
int	ft_get_fd1(t_token **head, int *fd1)
{
	t_token	*token;
	int		pipefds[2];

	token = *head;
	while (token && token->type != pipe_char)
	{
		if ((token->type == red_out || token->type == red_out_app)
			&& token->next->type == word)
		{
			if (token == *head)
				*head = token->next->next;
			if (token->type == red_out)
				*fd1 = open(token->next->value, O_CREAT | O_WRONLY, 0644);
			else
				*fd1 = open(token->next->value,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (*fd1 < 0)
				perror(token->next->value);
			ft_remove_token(token);
			ft_remove_token(token->next);
		}
		token = token->next;
	}
	if (!token)
		return (0);
	pipe(pipefds);
	*fd1 = pipefds[1];
	return (pipefds[0]);
}

char	**ft_get_args(t_token **head)
{
	t_token	*token;
	t_token	*prev;
	char	**strs;
	int		i;

	i = 0;
	token = *head;
	prev = token;
	while (token && token->type != pipe_char)
	{
		i++;
		prev = token;
		token = token->next;
	}
	token = prev;
	if (token)
		*head = token->next;
	strs = ft_malloc(sizeof(*strs) * (i + 1));
	strs[i] = NULL;
	while (i--)
	{
		prev = token->prev;
		strs[i] = ft_strdup(token->value);
		ft_remove_token(token);
		token = prev;
	}
	return (strs);
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
