#include "minishell.h"
#include <libc.h>

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	ft_open(const char *path, int oflag, mode_t mode)
{
	int	ret;

	ret = open(path, oflag, mode);
	if (ret < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
