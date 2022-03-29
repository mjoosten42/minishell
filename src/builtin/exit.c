#include "libft.h"

void	ft_exit(char *str)
{
	ft_putstr("exit\n");
	if (str)
		exit(ft_atoi(str));
	exit(EXIT_SUCCESS);
}
