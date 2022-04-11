#include "minishell.h"
#include "libft.h"
#include <libc.h>

char	*cd_path(char *path);

void	cd(char *path)
{
	t_program_data	*pd;
	char			*str;

	pd = pd_get();
	path = cd_path(path);
	if (!path)
		return ;
	free(pd->pwd);
	pd->pwd = NULL;
	pd->pwd = getcwd(pd->pwd, 0);
	unset("PWD");
	str = ft_strjoin("PWD=", pd->pwd);
	export(str);
	free(str);
	unset("OLDPWD");
	str = ft_strjoin("OLDPWD=", pd->pwd);
	export(str);
	free(str);
}

char	*cd_path(char *path)
{
	if (!path)
	{
		path = ft_get_env_from_pd("HOME");
		if (!path)
			ft_putendl_fd("cd: HOME not set", 2);
	}
	else if (!ft_strncmp(path, "-", ft_strlen(path)))
	{
		path = ft_get_env_from_pd("OLDPWD");
		if (!path)
			ft_putendl_fd("cd: OLDPWD not set", 2);
	}
	else if (chdir(path) < 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		path = NULL;
	}
	return (path);
}
