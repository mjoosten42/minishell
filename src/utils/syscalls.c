/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:10:15 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:10:23 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libc.h>

pid_t	ft_fork(void)
{
	t_program_data	*pd;
	pid_t			pid;

	pd = pd_get();
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	pd->active_processes++;
	return (pid);
}

int	ft_pipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	ft_dup2(int fildes, int fildes2)
{
	int	ret;

	ret = dup2(fildes, fildes2);
	if (ret < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	ft_close(int fildes)
{
	int	ret;

	ret = close(fildes);
	if (ret < 0)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
