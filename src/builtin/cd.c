#include "minishell.h"
#include "libft.h"
#include <libc.h>

void	replace_pwd(char *path)
{
	char *new_str;

	free(g_pd.oldpwd);
	g_pd.oldpwd = ft_get_env_from_pd("PWD");
	unset("OLDPWD");
	new_str = ft_strjoin("OLDPWD=", g_pd.pwd);
	export(new_str);
	free(new_str);
	unset("PWD");
	new_str = ft_strjoin("PWD=", path);
	export(new_str);
	free(new_str);
}

void	cd(char *path)
{
	if (!path)
	{
		path = ft_get_env_from_pd("HOME");
		if (!*path)
		{
			free(path);
			return (ft_putendl_fd("cd: HOME not set", 2));
		}
	}
	if (!ft_strncmp(path, "-", 2))
		path = g_pd.oldpwd;
	chdir(path);
	free(g_pd.pwd);
	g_pd.pwd = NULL;
	g_pd.pwd = getcwd(g_pd.pwd, 0);
	replace_pwd(g_pd.pwd);
}
