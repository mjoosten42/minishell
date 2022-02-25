/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:24:41 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/25 16:08:07 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char *str)
{
	pid_t		pid;
	char		**strs;
	char		*path;

	strs = ft_split(str, ' ');
	path = ft_getpath(*strs);
	if (!path)
		return (ft_putstr_fd("No such command\n", 2));
	pid = fork();
	if (!pid)
		if (execve(path, strs, 0) < 0)
			ft_error(0);
	waitpid(pid, 0, 0);
	free(path);
	ft_free_array((void **)strs);
}

char	*ft_getpath(char *str)
{
	static char	**paths;
	char		*path;
	int			i;

	i = 0;
	if (!access(str, F_OK))
		return (ft_strdup(str));
	if (!paths)
		paths = ft_getpaths();
	while (paths[i])
	{
		path = ft_strjoin(paths[i], str);
		if (!access(path, F_OK))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	**ft_getpaths(void)
{
	char	**strs;
	char	*str;
	int		i;

	i = 0;
	strs = ft_split(getenv("PATH"), ':');
	if (!strs)
		ft_error(0);
	while (strs[i])
	{
		str = ft_strjoin(strs[i], "/");
		free(strs[i]);
		strs[i] = str;
		i++;
	}
	return (strs);
}
