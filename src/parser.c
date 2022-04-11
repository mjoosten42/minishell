#include "minishell.h"
#include "libft.h"
#include "fcntl.h"

char	**ft_get_args(t_token *token);
int		ft_get_fds(t_token *token, int fds[2]);
int		ft_get_pipe(t_token *token, int fds[2]);
int		ft_redirect(t_token *token, int *fd, int flags);

void	ft_parse(t_token *head, int pipefd)
{
	char	**strs;
	int		fds[2];

	fds[0] = pipefd;
	fds[1] = STDOUT_FILENO;
	pipefd = ft_get_fds(head, fds);
	if (pipefd < 0)
		return ;
	strs = ft_get_args(head);
	if (!*strs)
	{
		if (fds[0] > STDERR_FILENO)
			ft_close(fds[0]);
		if (fds[1] > STDERR_FILENO)
			ft_close(fds[1]);
		return (ft_putendl_fd("Syntax error: redirect missing commands", 2));
	}
	ft_exec(strs, fds);
	ft_free_array(strs);
	if (pipefd)
	{
		ft_remove_token(head->next);
		ft_parse(head, pipefd);
	}
	else
		wait(NULL);
}

char	**ft_get_args(t_token *token)
{
	char	**strs;
	int		size;

	size = 0;
	while (token->next && token->next->type != pipe_char)
	{
		size++;
		token = token->next;
	}
	strs = ft_malloc(sizeof(*strs) * (size + 1));
	strs[size] = NULL;
	while (size--)
	{
		strs[size] = ft_strdup(token->value);
		token = token->prev;
		ft_remove_token(token->next);
	}
	return (strs);
}

int	ft_get_fds(t_token *token, int fds[2])
{
	t_token	*next;
	t_type	type;
	int		ret;

	ret = 0;
	while (token->next)
	{
		next = token->next;
		type = next->type;
		if (type == pipe_char)
			ret = ft_get_pipe(next, fds);
		else if (type == here_doc)
			ret = ft_here_doc(next, &fds[0]);
		else if (type == red_in)
			ret = ft_redirect(next, &fds[0], O_RDONLY);
		else if (type == red_out)
			ret = ft_redirect(next, &fds[1], O_WRONLY | O_CREAT);
		else if (type == red_out_app)
			ret = ft_redirect(next, &fds[1], O_WRONLY | O_CREAT | O_APPEND);
		else
			token = token->next;
		if (ret)
			return (ret);
	}
	return (0);
}

int	ft_get_pipe(t_token *token, int fds[2])
{
	int	pipefds[2];

	if (fds[1] > STDERR_FILENO)
		ft_close(fds[1]);
	if (token->prev->type != word || !token->next)
	{
		if (fds[0] > STDERR_FILENO)
			ft_close(fds[0]);
		return (ft_return_error("Syntax error: pipe missing commands"));
	}
	ft_pipe(pipefds);
	fds[1] = pipefds[1];
	return (pipefds[0]);
}

int	ft_redirect(t_token *token, int *fd, int flags)
{
	token = token->prev;
	ft_remove_token(token->next);
	token = token->next;
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	if (!token || token->type != word)
		return (ft_return_error("Syntax error: expected redirect target"));
	*fd = ft_open(token->value, flags, 0644);
	ft_remove_token(token);
	return (0);
}
