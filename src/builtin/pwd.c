#include "minishell.h"
#include "libft.h"

void	pwd(void)
{
	ft_putendl_fd(g_pd.dir, 1);
}
