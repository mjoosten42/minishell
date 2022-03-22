#include "minishell.h"
#include "libft.h"

void	export(t_program_data *pd, char *variable)
{
	char	**new_env;
	int		new_env_size;
	int		current_env_var;

	current_env_var = 0;
	new_env_size = pd->amount_env_lines + 2;
	new_env = ft_malloc(new_env_size * sizeof(char *));
	while (pd->env[current_env_var])
	{
		new_env[current_env_var] = pd->env[current_env_var];
		current_env_var++;
	}
	new_env[current_env_var] = ft_strdup(variable);
	new_env[current_env_var + 1] = NULL;
	free(pd->env);
	pd->env = new_env;
	pd->amount_env_lines = current_env_var + 1;
}
