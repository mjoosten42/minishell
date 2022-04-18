#include "minishell.h"
#include "libft.h"

void	ft_close_fds(int fds[2]);
char	*ft_search_paths(char *str);
char	*ft_getpath(char *str);

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
		if (!path || !**args)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(*args, 2);
			ft_putendl_fd( ": command not found", 2);
			exit(127);
		}
		if (access(path, X_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			perror(*args);
			exit(126);
		}
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

	if (*str == '.' || ft_strchr(str, '/'))
	{
		if (access(str, F_OK) < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(str);
			exit(127);
		}
		return (str);
	}
	path = ft_search_paths(str);
	if (!path)
	{
		if (access(str, F_OK) < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(str);
			exit(127);
		}
	}
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
		return (NULL);
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
	return (NULL);
}
