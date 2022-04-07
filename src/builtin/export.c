#include "minishell.h"
#include "libft.h"

int	is_export_name_valid(char *str)
{
	int	strlen;
	int	i;

	strlen = ft_strlen(str);
	i = 0;
	while (i < strlen)
	{
		if (i == 0 && !(str[i] == '_' || ft_isalnum(str[i])))
			return (i);
		if (str[i] == '_' || ft_isalnum(str[i]))
			i++;
		else
			break ;
	}
	return (i);
}

int	is_export_valid(char *str)
{
	int i;
	int	eq_sign_pos;

	eq_sign_pos = ft_strchr(str, '=') - str;
	if (is_export_name_valid(str) != eq_sign_pos - 1)
		return (0);
	return (1);
}

void	export(char *variable)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!is_export_valid(variable))
		return (-1);
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
