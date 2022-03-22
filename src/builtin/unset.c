#include "minishell.h"
#include "libft.h"

void	unset(t_program_data *pd, char *var)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	str = ft_strjoin(var, "=");
	len = ft_strlen(str);
	while (pd->env[i] && ft_strncmp(str, pd->env[i], len))
		i++;
	if (!pd->env[i])
		return ;
	free(pd->env[i]);
	if (i != pd->amount_env_lines)
		pd->env[i] = pd->env[pd->amount_env_lines - 1];
	pd->env[pd->amount_env_lines - 1] = NULL;
	pd->amount_env_lines--;
	free(str);
}
