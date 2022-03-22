#include "minishell.h"
#include "libft.h"

void	env(t_program_data *pd)
{
	int	i;

	i = 0;
	while (pd->env[i])
		ft_putstr(pd->env[i++]);
}
