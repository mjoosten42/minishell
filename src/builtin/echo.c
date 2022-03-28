#include "libft.h"
#include <stdio.h>

void	echo(char **strs)
{
	int	nl;
	int	i;

	i = 1;
	nl = ft_strncmp(strs[1], "-n", 3);
	if (!nl)
		i++;
	while (strs[i])
	{
		ft_putstr(strs[i++]);
		ft_putchar(' ');
	}
	if (nl)
		putchar('\n');
}