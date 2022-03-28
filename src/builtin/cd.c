#include "minishell.h"
#include <libc.h>

void	cd(char *path)
{
	chdir(path);
	getcwd(g_pd.dir, PATH_MAX);
}
