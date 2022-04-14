#include "minishell.h"
#include "libft.h"

void	ft_close_fds(int fds[2]);
char	**ft_getpaths(void);
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
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	paths = ft_getpaths();
	if (!paths)
		return (ft_strjoin("./", str));
	if (!access(str, F_OK))
		return (ft_strdup(str));
	while (paths[i])
	{
		path = ft_strjoin(paths[i], str);
		if (!access(path, F_OK))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	**ft_getpaths(void)
{
	char	**strs;
	char	*str;
	int		i;

	i = 0;
	str = ft_get_env_from_pd("PATH");
	if (!str)
		return (NULL);
	strs = ft_split(str, ':');
	free(str);
	if (!strs)
		ft_error(NULL);
	while (strs[i])
	{
		str = ft_strjoin(strs[i], "/");
		free(strs[i]);
		strs[i] = str;
		i++;
	}
	return (strs);
}
