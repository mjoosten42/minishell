#include "minishell.h"
#include "libft.h"
#include "fcntl.h"

#define MODE 0644

int		ft_get_fds(t_token *token, int fds[3]);
int		ft_redirect(t_token *token, int flags);
char	**ft_get_args(t_token *head);
int		ft_argsize(t_token *token);

void	ft_parse(t_token *head, int pipefd)
{
	pid_t	pid;
	char	**strs;
	int		fds[3];

	fds[0] = pipefd;
	fds[1] = STDOUT_FILENO;
	fds[2] = STDERR_FILENO;
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

int	ft_get_fds(t_token *token, int fds[3])
{
	int	pipefds[2];
	int	type;

	token = token->next;
	while (token)
	{
		type = token->type;
		if (type == pipe_char)
		{
			ft_pipe(pipefds);
			fds[1] = pipefds[1];
			return (pipefds[0]);
		}
		if (type == heredoc)
			fds[0] = ft_heredoc(token);
		if (type == red_in)
			fds[0] = ft_redirect(token, O_RDONLY);
		if (type == red_out)
			fds[1] = ft_redirect(token, O_CREAT | O_WRONLY);
		if (type == red_out_app)
			fds[1] = ft_redirect(token, O_CREAT | O_WRONLY | O_APPEND);
		token = token->next;
	}
	return (0);
}

int	ft_redirect(t_token *token, int flags)
{
	int	fd;

	token = token->prev;
	ft_remove_token(token->next);
	token = token->next;
	if (!token)
		ft_error("Syntax error: expected redirect target");
	fd = ft_open(token->value, flags, MODE);
	if (fd < 0)
		perror(token->value);
	ft_remove_token(token);
	return (fd);
}

int	ft_argsize(t_token *token)
{
	int	size;

	size = 0;
	while (token && token->type != pipe_char)
	{
		size++;
		token = token->next;
	}
	return (size);
}

char	**ft_get_args(t_token *token)
{
	char	**strs;
	int		size;
	int		i;

	i = 0;
	size = ft_argsize(token->next);
	strs = ft_malloc(sizeof(*strs) * (size + 1));
	strs[size] = NULL;
	while (i < size)
	{
		strs[i] = ft_strdup(token->next->value);
		ft_remove_token(token->next);
		i++;
	}
	return (strs);
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
