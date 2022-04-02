#include "minishell.h"
#include "libft.h"

int	is_builtin(char **strs)
{
	size_t	str_len;

	if (!strs)
		return (0);
	str_len = ft_strlen(*strs);
	if (!ft_strncmp(*strs, "cd", str_len))
		cd(strs[1]);
	else if (!ft_strncmp(*strs, "echo", str_len))
		echo(strs);
	else if (!ft_strncmp(*strs, "env", str_len))
		env();
	else if (!ft_strncmp(*strs, "export", str_len))
		export(strs[1]);
	else if (!ft_strncmp(*strs, "pwd", str_len))
		pwd();
	else if (!ft_strncmp(*strs, "unset", str_len))
		unset(strs[1]);
	else
		return (0);
	return (1);
}
