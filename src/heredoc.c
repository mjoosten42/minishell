#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

void	ft_heredoc(t_token *ptr)
{
	pid_t	pid;
	int		fds[2];
	char	*end_doc;
	char	*str;

	if (ptr->next && ptr->next->type == space)
		ft_remove_token(ptr->next);
	if (!ptr->next || ptr->next->type != word)
		ft_error("No heredoc end");
	end_doc = ptr->next->value;
	pipe(fds);
	pid = ft_fork();
	if (!pid)
	{
		close(fds[0]);
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
	ft_remove_token(ptr->next);
	free(ptr->value);
	ptr->value = ft_strdup(ft_itoa(fds[0]));
	waitpid(pid, NULL, 0);
}
