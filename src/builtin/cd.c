#include "minishell.h"
#include <libc.h>

void	cd(t_program_data *pd, char *path)
{
	chdir(path);
	getcwd(pd->dir, PATH_MAX);
}
