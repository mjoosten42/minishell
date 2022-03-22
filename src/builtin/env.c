#include "minishell.h"

void	env(t_program_data *pd)
{
	int	i;

	i = 0;
	while (pd->env[i])
		printf("%s\n", pd->env[i++]);
}
