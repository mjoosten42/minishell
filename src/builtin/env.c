#include "minishell.h"
#include "libft.h"

void	env(void)
{
	int	i;

	i = 0;
	while (g_pd.env[i])
		ft_putstr(g_pd.env[i++]);
}
