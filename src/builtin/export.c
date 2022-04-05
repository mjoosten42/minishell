#include "minishell.h"
#include "libft.h"

void	export(char *variable)
{
	char	**new_env;
	int		i;

	i = 0;
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
