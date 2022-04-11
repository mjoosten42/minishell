#include "minishell.h"
#include "libft.h"

void	env(void)
{
	t_program_data	*pd;
	int				i;

	i = 0;
	pd = pd_get();
	while (pd->env[i])
		ft_putendl_fd(pd->env[i++], 1);
}
