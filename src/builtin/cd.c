#include "minishell.h"
#include <libc.h>

void	cd(char *path)
{
	chdir(path);
	free(g_pd.dir);
	g_pd.dir = NULL;
	g_pd.dir = getcwd(g_pd.dir, 0);
}
