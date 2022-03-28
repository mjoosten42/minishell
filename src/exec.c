#include "minishell.h"
#include "libft.h"

pid_t	ft_exec(char *path, char **args, int fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(0);
	if (!pid)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		execve(path, args, g_pd.env);
		ft_error(0);
	}
	if (fds[0] > 2)
		close(fds[0]);
	if (fds[1] > 2)
		close(fds[1]);
	return (pid);
}
