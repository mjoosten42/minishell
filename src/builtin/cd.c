#include "minishell.h"
#include <libc.h>

void	cd(char *path)
{
	if (!path)
	{
		free(path);
		path = ft_substr(ft_get_env_from_pd("HOME"), 5);
		printf("%s", path);
	}
	chdir(path);
	free(g_pd.dir);
	g_pd.dir = NULL;
	g_pd.dir = getcwd(g_pd.dir, 0);
}
