/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:09:20 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:09:21 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	unset_single("PWD");
	str = ft_strjoin("PWD=", pd->pwd);
	add_to_env(str);
	free(str);
	unset_single("OLDPWD");
	str = ft_strjoin("OLDPWD=", pd->pwd);
	add_to_env(str);
	free(str);
}

char	*cd_path(char *path)
{
	t_program_data	*pd;

	pd = pd_get();
	if (chdir(path) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		perror(path);
		path = NULL;
		pd->last_exit_status = 1;
	}
	return (path);
}
