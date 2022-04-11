#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

int	ft_heredoc_loop(char *end);

int	ft_here_doc(t_token *token, int *fd)
{
	token = token->prev;
	ft_remove_token(token->next);
	token = token->next;
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	if (!token || token->type != word)
		return (ft_return_error("Syntax error: expected heredoc delimiter"));
	g_pd.heredoc_sigint = 1;
	*fd = ft_heredoc_loop(token->value);
	g_pd.heredoc_sigint = 0;
	if (*fd < 0)
		return (-1);
	ft_remove_token(token);
	return (0);
}

int	ft_heredoc_loop(char *end)
{
	char	*str;
	int		fds[2];
	int		len;

	ft_pipe(fds);
	len = ft_strlen(end);
	while (1)
	{
		str = readline("> ");
		if (g_pd.heredoc_sigint == 2)
		{
			g_pd.heredoc_sigint = 0;
			return (-1);
		}
		if (!str || !ft_strncmp(str, end, len + 1))
			break ;
		write(fds[1], str, ft_strlen(str));
		write(fds[1], "\n", 1);
		free(str);
	}
	ft_close(fds[1]);
	return (fds[0]);
}
