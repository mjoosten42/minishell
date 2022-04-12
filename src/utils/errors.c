#include "minishell.h"
#include "libft.h"

int	nop(void)
{
	return (0);
}

int	ft_exit_string(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
	exit(exit_code);
}
