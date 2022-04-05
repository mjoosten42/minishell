#include "minishell.h"
#include "libft.h"
#include <libc.h>

void	replace_pwd(char *path)
{
	char *new_str;

	printf("le first printf");
	free(g_pd.old_pwd);
	g_pd.old_pwd = ft_get_env_from_pd("PWD");
	unset("OLDPWD");
	new_str = ft_strjoin("OLDPWD=", ft_get_env_from_pd("PWD"));
	export(new_str);
	free(new_str);
	printf("le second printf");
	unset("PWD");
	new_str = ft_strjoin("PWD=", path);
	export(new_str);
	free(new_str);
	printf("le third printf");
}

void	cd(char *path)
{
	if (!path)
	{
		path = ft_get_env_from_pd("HOME");
		printf("%s", path);
	}
	chdir(path);
	free(g_pd.pwd);
	g_pd.pwd = NULL;
	g_pd.pwd = getcwd(g_pd.pwd, 0);
	replace_pwd(g_pd.pwd);
}
