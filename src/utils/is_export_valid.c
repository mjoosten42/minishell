#include "minishell.h"
#include "libft.h"

int	is_export_valid(char *str)
{
	int	strlen;
	int	i;

	strlen = ft_strlen(str);
	i = 0;
	while (i < strlen)
	{
		if (i == 0 && !(str[i] == '_' || ft_isalnum(str[i])))
			return (i);
		if (str[i] == '_' || ft_isalnum(str[i]))
			i++;
		else
			break ;
	}
	return (i);
}
