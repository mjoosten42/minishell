/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:09:46 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:09:51 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		is_export_valid(char *str);
void	print_sorted_env(void);

void	export(char **strs)
{
	t_program_data	*pd;
	char			*str;
	int				len;
	int				i;

	i = 1;
	pd = pd_get();
	pd->last_exit_status = 0;
	if (!strs[1])
		print_sorted_env();
	while (strs[i])
	{
		len = is_export_valid(strs[i]);
		if (len)
		{
			str = ft_substr(strs[i], 0, len);
			unset_single(str);
			free(str);
			add_to_env(strs[i]);
		}
		else
			pd->last_exit_status = 1;
		i++;
	}
}

void	print_sorted_env(void)
{
	t_program_data	*pd;
	int				i;

	i = 0;
	pd = pd_get();
	sort(pd->env);
	while (pd->env[i])
	{
		ft_putstr("declare -x ");
		ft_putstr(pd->env[i]);
		ft_putstr("\n");
		i++;
	}
}

int	is_export_valid(char *str)
{
	char	*eq;
	int		eq_sign_pos;
	int		len;

	eq = ft_strchr(str, '=');
	eq_sign_pos = eq - str;
	len = export_name_len(str);
	if (!eq_sign_pos || len != eq_sign_pos)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (0);
	}
	return (len);
}

int	export_name_len(char *str)
{
	int	strlen;
	int	i;

	i = 0;
	strlen = ft_strlen(str);
	if (!(*str == '_' || ft_isalpha(*str)))
		return (0);
	while (i < strlen)
	{
		if (str[i] == '_' || ft_isalnum(str[i]))
			i++;
		else
			break ;
	}
	return (i);
}

void	add_to_env(char *str)
{
	t_program_data	*pd;
	char			**new_env;
	int				i;

	i = 0;
	pd = pd_get();
	pd->amount_env_lines++;
	new_env = ft_malloc((pd->amount_env_lines + 1) * sizeof(char *));
	while (pd->env[i])
	{
		new_env[i] = pd->env[i];
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	free(pd->env);
	pd->env = new_env;
}
