#include "minishell.h"
#include "libft.h"
#include <sys/stat.h>

void	ft_close_fds(int fds[2]);
char	*ft_search_paths(char *str);
char	*ft_getpath(char *str);
char	*find_local(char *str);

void	ft_exec(char **args, int fds[2])
{
	t_program_data	*pd;
	pid_t			pid;
	char			*path;

	if (!*args || is_builtin_unforked(args))
		return (ft_close_fds(fds));
	pd = pd_get();
	pid = ft_fork();
	if (!pid)
	{
		ft_dup2(fds[0], STDIN_FILENO);
		ft_dup2(fds[1], STDOUT_FILENO);
		if (is_builtin_forked(args))
			exit(EXIT_SUCCESS);
		path = ft_getpath(*args);
		if (!path)
			return ;
		execve(path, args, pd->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	ft_close_fds(fds);
}

void	ft_close_fds(int fds[2])
{
	if (fds[0] > STDERR_FILENO)
		ft_close(fds[0]);
	if (fds[1] > STDERR_FILENO)
		ft_close(fds[1]);
}

char	*ft_getpath(char *str)
{
	char	*path;

	path = NULL;
	if (*str != '.' && !ft_strchr(str, '/'))
		path = ft_search_paths(str);
	else
		path = find_local(str);
	return (path);
}

char	*ft_search_paths(char *str)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_get_env_from_pd("PATH");
	if (!tmp)
		return (find_local(str));
	paths = ft_split(tmp, ':');
	free(tmp);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, str);
		free(tmp);
		if (!access(paths[i], F_OK))
		{
			tmp = ft_strdup(paths[i]);
			ft_free_array(paths);
			return (tmp);
		}
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found", 2);
	exit((1 << 7) - 1);
}

char	*find_local(char *str)
{
	struct stat	buf;

	if (!ft_strncmp(str, ".", 2))
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		exit(2);
	}
	stat(str, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": is a directory", 2);
		exit((1 << 7) - 2);
	}
	if (access(str, F_OK | F_OK) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(str);
		if (access(str, F_OK))
			exit((1 << 7) - 1);
		exit((1 << 7) - 2);
	}
	return (str);
}
