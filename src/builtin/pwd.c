#include "minishell.h"
#include "libft.h"

void	pwd(t_program_data *pd)
{
	ft_putstr(pd->dir);
	ft_putchar('\n');
}
