/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:34 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/25 12:05:04 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;

	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			ft_exit();
		printf("str: [%s]\n", str);
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
		ft_putchar_fd(BACKSPACE, 0);
		ft_putchar_fd(BACKSPACE, 0);
		ft_putchar_fd('\n', 0);
		rl_on_new_line();
	}
	if (signum == SIGQUIT)
	{
		ft_putchar_fd(BACKSPACE, 0);
		ft_putchar_fd(BACKSPACE, 0);
	}
}

void	ft_parse(char *str)
{
	char	**strs;

	strs = ft_split(str, ' ');
	if (!strs)
		return ;
	if (!ft_strncmp(*strs, "exit", 4))
		exit(EXIT_SUCCESS);
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
	ft_free_array((void **)strs);
}

void	ft_exit(void)
{
	ft_putchar_fd(BACKSPACE, 0);
	ft_putchar_fd(BACKSPACE, 0);
	ft_putstr_fd("exit\n", 0);
	exit(EXIT_SUCCESS);
}
