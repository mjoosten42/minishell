#include "minishell.h"
#include "libft.h"

int	ft_return_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (-1);
}

int	ft_heredoc_return(void)
{
	g_pd.signalled = 0;
	return (-1);
}

int	nop(void)
{
	return (0);
}
