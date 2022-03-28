/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjoosten <mjoosten@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/28 11:15:04 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/03/28 11:58:12 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_builtin(char **strs)
{
	size_t	str_len;

	str_len = ft_strlen(*strs);
	if (!ft_strncmp(*strs, "cd", str_len))
		cd(strs[1]);
	else if (!ft_strncmp(*strs, "echo", str_len))
		echo(strs);
	else if (!ft_strncmp(*strs, "env", str_len))
		env();
	else if (!ft_strncmp(*strs, "exit", str_len))
		ft_exit();
	else if (!ft_strncmp(*strs, "export", str_len))
		export(strs[1]);
	else if (!ft_strncmp(*strs, "pwd", str_len))
		pwd();
	else if (!ft_strncmp(*strs, "unset", str_len))
		unset(strs[1]);
	else
		return (0);
	return (1);
}
