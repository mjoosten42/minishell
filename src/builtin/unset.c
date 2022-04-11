#include "minishell.h"
#include "libft.h"

void	unset(char *var)
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
