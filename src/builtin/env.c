/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:09:37 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/26 10:23:48 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	env(void)
{
	t_program_data	*pd;
	int				i;

	i = 0;
	pd = pd_get();
	while (pd->env[i])
		ft_putendl_fd(pd->env[i++], 1);
}

char	*ft_get_env_from_pd(char *str)
{
	t_program_data	*pd;
	char			*tmp;
	int				len;
	int				i;

	i = 0;
	pd = pd_get();
	tmp = ft_strjoin(str, "=");
	len = ft_strlen(tmp);
	while (pd->env[i] && ft_strncmp(pd->env[i], tmp, len))
		i++;
	free(tmp);
	if (!pd->env[i])
		return (NULL);
	len = 0;
	while (pd->env[i][len] != '=')
		len++;
	return (ft_substr(pd->env[i], len + 1, ft_strlen(pd->env[i]) - len));
}
