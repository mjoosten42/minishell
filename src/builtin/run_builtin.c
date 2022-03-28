/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:15:04 by rnijhuis          #+#    #+#             */
/*   Updated: 2022/03/28 11:49:46 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_builtin(char **strs)
{
	size_t	str_len;

	str_len = ft_strlen(*strs);
	if (ft_strncmp(*strs, "cd", str_len))
		cd(str[1])
	else if (ft_strncmp(str, "echo", str_len))
		echo(str);
	else if (ft_strncmp(str, "env", str_len))
		env();
	else if (ft_strncmp(str, "exit", str_len))
		ft_exit();
	else if (ft_strncmp(str, "export", str_len))
		ft_export()
	else if (ft_strncmp(str, "pwd", str_len))
		pwd();
	else if (ft_strncmp(str, "unset", str_len))
		unset(str[0]);
	else
		return (0);
	return (1);
}
