#include "libft.h"
#include <stdio.h>

void	echo(char **strs)
{
	int	nl;
	int	i;

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
