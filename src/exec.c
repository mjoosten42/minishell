#include "minishell.h"
#include "libft.h"

void	ft_dup_fds(int fds[2]);
void	ft_close_fds(int fds[2]);

pid_t	ft_exec(char **args, int fds[2])
{
	pid_t	pid;
	char	*path;

	if (!*args || is_builtin_unforked(args))
		return (0);
	pid = ft_fork();
	if (!pid)
	{
		ft_dup_fds(fds);
		if (is_builtin_forked(args))
			exit(EXIT_SUCCESS);
		path = ft_getpath(*args);
		if (!path)
			ft_error(ft_strjoin(*args, ": command not found"));
		execve(path, args, g_pd.env);
		ft_error(0);
	}
	ft_close_fds(fds);
	return (pid);
}

void	ft_dup_fds(int fds[2])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (dup2(fds[i], i) < 0)
			ft_error("dup2");
		i++;
	}
}

void	ft_close_fds(int fds[2])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (fds[i] > STDERR_FILENO)
			close(fds[i]);
		i++;
	}
}
