#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

void	ft_heredoc_child(int fds[2]);

int	ft_heredoc(t_token *token)
{
	pid_t	pid;
	int		fds[2];

	token = token->prev;
	ft_remove_token(token->next);
	token = token->next;
	if (!token || token->type != word)
		ft_error("Syntax error: expected redirect target");
	ft_pipe(fds);
	pid = ft_fork();
	if (!pid)
		ft_heredoc_child(fds);
	close(fds[1]);
	waitpid(pid, NULL, 0);
	ft_remove_token(token);
	return (fds[0]);
}

void	ft_heredoc_child(int fds[2])
{
	char	*str;

	close(fds[0]);
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strncmp(token->value, str, ft_strlen(token->value)))
			break ;
		write(fds[1], str, ft_strlen(str));
		write(fds[1], "\n", 1);
	}
	exit(EXIT_SUCCESS);
}
