#include "minishell.h"
#include "libft.h"

void	pwd(void)
{
	t_program_data	*pd;

	pd = pd_get();
	ft_putendl_fd(pd->pwd, 1);
}
