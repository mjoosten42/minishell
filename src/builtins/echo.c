#include "libft.h"

void	ft_echo(char **strs)
{
	int	i;
	int	nl;

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
