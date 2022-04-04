#include "minishell.h"
#include "libft.h"

pid_t	ft_exec(char **args, int fds[2])
{
	pid_t	pid;
	char	*path;

	if (!*args || is_builtin_unforked(args))
		return (0);
	pid = ft_fork();
	if (!pid)
	{
		ft_dup2(fds[0], STDIN_FILENO);
		ft_dup2(fds[1], STDOUT_FILENO);
		if (is_builtin_forked(args))
			exit(EXIT_SUCCESS);
		path = ft_getpath(*args);
		if (!path)
			ft_error(ft_strjoin(*args, ": command not found"));
		execve(path, args, g_pd.env);
		ft_error(0);
	}
	if (fds[0] > STDERR_FILENO)
		ft_close(fds[0]);
	if (fds[1] > STDERR_FILENO)
		ft_close(fds[1]);
	return (pid);
}
