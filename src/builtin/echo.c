#include "libft.h"
#include "minishell.h"
#include <stdio.h>

void	echo(char **strs)
{
	t_program_data	*pd;
	int				nl;
	int				i;

	pd = pd_get();
	pd->last_exit_status = 0;
	if (!strs[1])
	{
		ft_putchar('\n');
		return ;
	}
	i = 1;
	nl = ft_strncmp(strs[1], "-n", 3);
	if (!nl)
		i++;
	while (strs[i])
	{
		ft_putstr(strs[i]);
		if (strs[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (nl)
		ft_putchar('\n');
}
