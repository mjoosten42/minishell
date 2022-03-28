/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:36:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/28 11:37:18 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

char	*ft_getpath(char *str)
{
	static char	**paths;
	char		*path;
	int			i;

	i = 0;
	if (!paths)
		paths = ft_getpaths();
	if (!access(str, F_OK))
		return (ft_strdup(str));
	while (paths[i])
	{
		path = ft_strjoin(paths[i], str);
		if (!access(path, F_OK))
			return (path);
		free(path);
		i++;
	}
	ft_putstr_fd(rl_line_buffer, 2);
	ft_putstr_fd(": command not found\n", 2);
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
		ft_error(NULL);
	while (strs[i])
	{
		str = ft_strjoin(strs[i], "/");
		free(strs[i]);
		strs[i] = str;
		i++;
	}
	return (strs);
}

pid_t	ft_exec(char *path, char **args, int fd0, int fd1)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(0);
	if (!pid)
	{
		dup2(fd0, STDIN_FILENO);
		dup2(fd1, STDOUT_FILENO);
		execve(path, args, g_pd.env);
		perror(0);
	}
	close(fd0);
	close(fd1);
	return (pid);
}
