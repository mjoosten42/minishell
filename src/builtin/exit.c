#include "libft.h"
#include "limits.h"

void	ft_exit(char *str)
{
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	if (str)
		exit(ft_atoi(str));
	exit(EXIT_SUCCESS);
}

int		ft_isvalid(char *str)
{
	int64_t		number;
	int			min;

	min = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (!str)
		return (0);
	if (*str == '-')
	{
		min++;
		str++;
	}
	if (ft_strlen(str) > 19)
		return (0);
	number = 0;
	while (*str)
		number = 10 * number + *str++ - '0';
	if (number < LONG_MIN || number > LONG_MAX)
		return (0);
	return (1);
}
