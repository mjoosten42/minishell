#include "minishell.h"
#include "libft.h"

void	export(t_program_data *pd, char *variable)
{
	char	**new_env;
	int		new_env_size;
	int		i;

	i = 0;
	new_env_size = pd->amount_env_lines + 2;
	new_env = ft_malloc(new_env_size * sizeof(char *));
	while (pd->env[i])
	{
		new_env[i] = pd->env[i];
		i++;
	}
	new_env[i] = ft_strdup(variable);
	new_env[i + 1] = NULL;
	free(pd->env);
	pd->env = new_env;
	pd->amount_env_lines++;
}
