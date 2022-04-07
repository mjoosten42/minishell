#include "minishell.h"
#include "libft.h"

int	is_export_valid(char *str);
int	export_name_len(char *str);

void	export(char *variable)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!is_export_valid(variable))
		return ;
	g_pd.amount_env_lines++;
	new_env = ft_malloc((g_pd.amount_env_lines + 1) * sizeof(char *));
	while (g_pd.env[i])
	{
		new_env[i] = g_pd.env[i];
		i++;
	}
	new_env[i] = ft_strdup(variable);
	new_env[i + 1] = NULL;
	free(g_pd.env);
	g_pd.env = new_env;
}

int	is_export_valid(char *str)
{
	char	*id;
	char	*eq;
	int		eq_sign_pos;
	int		len;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (0);
	eq_sign_pos = eq - str;
	len = export_name_len(str);
	if (len != eq_sign_pos)
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (0);
	}
	id = ft_substr(str, 0, len);
	unset(id);
	free(id);
	return (1);
}

int	export_name_len(char *str)
{
	int	strlen;
	int	i;

	i = 0;
	strlen = ft_strlen(str);
	if (!(*str == '_' || ft_isalnum(*str)))
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
