#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

int	ft_heredoc_return(void);

int	ft_here_doc(t_token *token, int *fd)
{
	char	*str;
	int		fds[2];
	int		len;

	token = token->prev;
	ft_remove_token(token->next);
	token = token->next;
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	if (!token || token->type != word)
		return (ft_return_error("Syntax error: expected heredoc delimiter"));
	len = ft_strlen(token->value);
	ft_pipe(fds);
	g_pd.signalled = 1;
	while (1)
	{
		str = readline("> ");
		if (g_pd.signalled == 2)
			return (ft_heredoc_return());
		if (!str || !ft_strncmp(str, token->value, len + 1))
			break ;
		write(fds[1], str, ft_strlen(str));
		write(fds[1], "\n", 1);
		free(str);
	}
	g_pd.signalled = 0;
	ft_close(fds[1]);
	ft_remove_token(token);
	*fd = fds[0];
	return (0);
}
