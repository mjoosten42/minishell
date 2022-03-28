#include "minishell.h"
#include "libft.h"

void	pwd(void)
{
	ft_putstr(g_pd.dir);
	ft_putchar('\n');
}
