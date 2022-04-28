/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:12:22 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:12:23 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_env_len(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
		i++;
	return (i);
}

int	is_sorted(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		if (envs[i + 1] != NULL)
			if (ft_strncmp(envs[i], envs[i + 1], ft_strlen(envs[i])) > 0)
				return (0);
		i++;
	}
	return (1);
}

void	sort(char **envs)
{
	int		i;
	int		env_len;
	char	*tmp;

	env_len = get_env_len(envs);
	while (is_sorted(envs) == 0)
	{
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strncmp(envs[i], envs[i + 1], ft_strlen(envs[i])) > 0)
			{
				tmp = envs[i];
				envs[i] = envs[i + 1];
				envs[i + 1] = tmp;
			}
			i++;
		}
	}
}
