#include "minishell.h"
#include "libft.h"
#include <libc.h>

void	replace_oldpwd(void);
char	*cd_path(char *path);

void	cd(char *path)
{
	char	*str;

	path = cd_path(path);
	replace_oldpwd();
	free(g_pd.pwd);
	g_pd.pwd = NULL;
	g_pd.pwd = getcwd(g_pd.pwd, 0);
	unset("PWD");
	str = ft_strjoin("PWD=", g_pd.pwd);
	export(str);
	free(str);
}

char	*cd_path(char *path)
{
	if (!path)
	{
		path = ft_get_env_from_pd("HOME");
		if (!*path)
		{
			free(path);
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
	}
	if (!ft_strncmp(path, "-", ft_strlen(path)))
		path = g_pd.oldpwd;
	if (chdir(path) < 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (NULL);
	}
	return (path);
}

void	replace_oldpwd(void)
{
	char	*new_str;

	free(g_pd.oldpwd);
	g_pd.oldpwd = ft_strdup(g_pd.pwd);
	unset("OLDPWD");
	new_str = ft_strjoin("OLDPWD=", g_pd.pwd);
	export(new_str);
	free(new_str);
}
