#include "minishell.h"
#include "libft.h"
#include <libc.h>

char	*cd_path(char *path);

void	cd(char *path)
{
	t_program_data	*pd;
	char			*str;

	pd = pd_get();
	pd->last_exit_status = 0;
	path = cd_path(path);
	if (!path)
		return ;
	free(pd->pwd);
	pd->pwd = NULL;
	pd->pwd = getcwd(pd->pwd, 0);
	unset("PWD");
	str = ft_strjoin("PWD=", pd->pwd);
	add_to_env(str);
	free(str);
	unset("OLDPWD");
	str = ft_strjoin("OLDPWD=", pd->pwd);
	add_to_env(str);
	free(str);
}

char	*cd_path(char *path)
{
	t_program_data	*pd;

	pd = pd_get();
	if (!path)
	{
		path = ft_get_env_from_pd("HOME");
		if (!path)
			ft_putendl_fd("cd: HOME not set", 2);
		pd->last_exit_status = 1;
	}
	else if (!ft_strncmp(path, "-", ft_strlen(path)))
	{
		path = ft_get_env_from_pd("OLDPWD");
		if (!path)
			ft_putendl_fd("cd: OLDPWD not set", 2);
		pd->last_exit_status = 1;
	}
	else if (chdir(path) < 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		path = NULL;
		pd->last_exit_status = 1;
	}
	return (path);
}
