#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

int	ft_heredoc(t_token *ptr)
{
	pid_t	pid;
	int		fds[2];
	char	*end_doc;
	char	*str;

	pipe(fds);
	pid = ft_fork();
	if (!pid)
	{
		close(fds[0]);
		end_doc = ptr->next->value;
		while (1)
		{
			str = readline("> ");
			if (!str || !ft_strncmp(end_doc, str, ft_strlen(end_doc)))
				break ;
			write(fds[1], str, ft_strlen(str));
			write(fds[1], "\n", 1);
		}
		exit(EXIT_SUCCESS);
	}
	close(fds[1]);
	waitpid(pid, NULL, 0);
	return (fds[0]);
}
