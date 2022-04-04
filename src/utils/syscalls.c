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

int	ft_pipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	ft_dup2(int fildes, int fildes2)
{
	int	ret;

	ret = dup2(fildes, fildes2);
	if (ret < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	ft_close(int fildes)
{
	int	ret;

	ret = close(fildes);
	if (ret < 0)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
