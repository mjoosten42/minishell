/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:10:03 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:10:04 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	unset_single(char *var)
{
	t_program_data	*pd;
	char			*str;
	int				len;
	int				i;

	i = 0;
	pd = pd_get();
	str = ft_strjoin(var, "=");
	len = ft_strlen(str);
	while (pd->env[i] && ft_strncmp(str, pd->env[i], len))
		i++;
	free(str);
	if (!pd->env[i])
		return ;
	free(pd->env[i]);
	if (i != pd->amount_env_lines)
		pd->env[i] = pd->env[pd->amount_env_lines - 1];
	pd->env[pd->amount_env_lines - 1] = NULL;
	pd->amount_env_lines--;
}

void	unset(char **strs)
{
	t_program_data	*pd;
	int				i;

	i = 1;
	pd = pd_get();
	pd->last_exit_status = 0;
	while (strs[i])
	{
		unset_single(strs[i]);
		i++;
	}
}
