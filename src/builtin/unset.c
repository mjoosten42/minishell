#include "minishell.h"
#include "libft.h"

void	unset(char *var)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	str = ft_strjoin(var, "=");
	len = ft_strlen(str);
	while (g_pd.env[i] && ft_strncmp(str, g_pd.env[i], len))
		i++;
	free(str);
	free(g_pd.env[i]);
	if (!g_pd.env[i])
		return ;
	if (i != g_pd.amount_env_lines)
		g_pd.env[i] = g_pd.env[g_pd.amount_env_lines - 1];
	g_pd.env[g_pd.amount_env_lines - 1] = NULL;
	g_pd.amount_env_lines--;
}
