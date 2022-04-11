#include "minishell.h"
#include "libft.h"

int	ft_return_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (-1);
}

int	nop(void)
{
	return (0);
}

int	ft_exit_string(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
	exit(exit_code);
}
