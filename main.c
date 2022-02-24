/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/24 16:37:21 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	char	c;

	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			c = 8;
			write(0, &c, 1);
			write(0, &c, 1);
			write(0, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		if (!*str)
			continue ;
		add_history(str);
		ft_parse(str);
		free(str);
	}
}

void	ft_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\nminishell$ ");
		free(rl_line_buffer);
		rl_line_buffer = 0;
	}
}

void	ft_parse(char *str)
{
	char	**strs;

	strs = ft_split(str, ' ');
	ft_builtins(strs);
	ft_free_array((void **)strs);
}

void	ft_builtins(char **strs)
{
	char	*str;

	if (!ft_strncmp(*strs, "exit", 4))
		exit(ft_atoi(strs[1]));
	if (!ft_strncmp(*strs, "echo", 4))
		ft_putendl_fd(strs[1], 1);
	if (!ft_strncmp(*strs, "pwd", 3))
	{
		str = getcwd(0, PATH_MAX);
		ft_putendl_fd(str, 1);
		free(str);
	}
	if (!ft_strncmp(*strs, "cd", 2))
		chdir(strs[1]);
}
