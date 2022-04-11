#include "minishell.h"
#include "libft.h"

char	**ft_getpaths(void);
char	*ft_getpath(char *str);

void	ft_exec(char **args, int fds[2])
{
	pid_t	pid;
	char	*path;

	if (!*args || is_builtin_unforked(args))
		return ;
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
		perror("minishell");
		exit(EXIT_FAILURE);
	}
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
