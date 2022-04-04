#include "minishell.h"
#include "libft.h"
#include "fcntl.h"

char	**ft_get_args(t_token *token);
int		ft_get_fds(t_token *token, int fds[2]);
void	ft_redirect(t_token *token, int *fd, int flags);
int		ft_get_pipe(int *fd);

void	ft_parse(t_token *head, int pipefd)
{
	pid_t	pid;
	char	**strs;
	int		fds[2];

	fds[0] = pipefd;
	fds[1] = STDOUT_FILENO;
	pipefd = ft_get_fds(head, fds);
	strs = ft_get_args(head);
	pid = ft_exec(strs, fds);
	ft_free_array(strs);
	if (pipefd)
	{
		ft_remove_token(head->next);
		ft_parse(head, pipefd);
	}
	else
		waitpid(pid, NULL, 0);
}

int	ft_get_fds(t_token *token, int fds[2])
{
	int	type;

	token = token->next;
	while (token)
	{
		type = token->type;
		if (type == pipe_char)
			return (ft_get_pipe(&fds[1]));
		if (type == heredoc)
			ft_heredoc(token, &fds[0]);
		if (type == red_in)
			ft_redirect(token, &fds[0], O_RDONLY);
		if (type == red_out)
			ft_redirect(token, &fds[1], O_WRONLY | O_CREAT);
		if (type == red_out_app)
			ft_redirect(token, &fds[1], O_WRONLY | O_CREAT | O_APPEND);
		token = token->next;
	}
	return (0);
}

void	ft_redirect(t_token *token, int *fd, int flags)
{
	token = token->prev;
	ft_remove_token(token->next);
	token = token->next;
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	if (!token)
		ft_error("Syntax error: expected redirect target");
	*fd = ft_open(token->value, flags, 0644);
	ft_remove_token(token);
}

int	ft_get_pipe(int *fd)
{
	int	pipefds[2];

	ft_pipe(pipefds);
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	*fd = pipefds[1];
	return (pipefds[0]);
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
