#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

static char	**ft_getpaths(void);

char	*ft_getpath(char *str)
{
	static char	**paths;
	char		*path;
	int			i;

	i = 0;
	if (!paths)
		paths = ft_getpaths();
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
	ft_putstr_fd(rl_line_buffer, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}

static char	**ft_getpaths(void)
{
	char	**strs;
	char	*str;
	int		i;

	i = 0;
	strs = ft_split(getenv("PATH"), ':');
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
