#include "libft.h"
#include "limits.h"

int		ft_isvalid(char *str);

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
