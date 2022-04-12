#include "libft.h"

int	is_all_digits(char *str)
{
	int strlen;
	int i;

	strlen = ft_strlen(str);
	i = 0;
	while (i < strlen)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **strs)
{
	if (strs[2] && is_all_digits(strs[2]))
		
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (strs[1])
		exit(ft_atoi(strs[1]));
	exit(EXIT_SUCCESS);
}
