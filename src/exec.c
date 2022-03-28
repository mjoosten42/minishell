#include "minishell.h"
#include "libft.h"

pid_t	ft_exec(char *path, char **args, int fd0, int fd1)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(0);
	if (!pid)
	{
		dup2(fd0, STDIN_FILENO);
		dup2(fd1, STDOUT_FILENO);
		execve(path, args, g_pd.env);
		perror(0);
	}
	if (fd0 > 2)
		close(fd0);
	if (fd1 > 2)
		close(fd1);
	return (pid);
}
