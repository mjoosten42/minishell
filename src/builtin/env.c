#include "minishell.h"
#include "libft.h"

void	env(void)
{
	int	i;

	i = 0;
	while (g_pd.env[i])
		ft_putendl_fd(g_pd.env[i++], 1);
}
