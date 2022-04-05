#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

void	ft_heredoc_child(int fds[2], char *end);
void	ft_heredoc_signal(int signum);
void	ft_signal(int signum);

int	ft_heredoc(t_token *token, int *fd)
{
	pid_t	pid;
	int		fds[2];

	token = token->prev;
	ft_remove_token(token->next);
	token = token->next;
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	if (!token || token->type != word)
		return (ft_return_error("Syntax error: expected heredoc delimiter"));
	ft_pipe(fds);
	pid = ft_fork();
	if (!pid)
		ft_heredoc_child(fds, token->value);
	close(fds[1]);
	waitpid(pid, NULL, 0);
	ft_remove_token(token);
	*fd = fds[0];
	return (WEXITSTATUS(g_pd.last_exit_status));
}

void	ft_heredoc_child(int fds[2], char *end)
{
	char	*str;
	int		len;

	close(fds[0]);
	len = ft_strlen(end);
	signal(SIGINT, ft_heredoc_signal);
	while (1)
	{
		str = readline("> ");
		printf("str: %s\n", str);
		if (!str || !ft_strncmp(str, end, len))
			break ;
		write(fds[1], str, ft_strlen(str));
		write(fds[1], "\n", 1);
	}
	exit(EXIT_SUCCESS);
}

void	ft_heredoc_signal(int signum)
{
	(void)signum;
	exit(EXIT_SUCCESS);
}
