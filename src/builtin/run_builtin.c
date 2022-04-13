#include "minishell.h"
#include "libft.h"

int	is_builtin_unforked(char **strs)
{
	size_t	str_len;

	if (!strs)
		return (0);
	str_len = ft_strlen(*strs) + 1;
	if (!ft_strncmp(*strs, "unset", str_len))
		unset(strs[1]);
	else if (!ft_strncmp(*strs, "cd", str_len))
		cd(strs[1]);
	else if (!ft_strncmp(*strs, "exit", str_len))
		ft_exit(strs);
	else if (!ft_strncmp(*strs, "export", str_len))
		export(strs);
	else
		return (0);
	return (1);
}

int	is_builtin_forked(char **strs)
{
	size_t	str_len;

	if (!strs)
		return (0);
	str_len = ft_strlen(*strs) + 1;
	if (!ft_strncmp(*strs, "env", str_len))
		env();
	else if (!ft_strncmp(*strs, "echo", str_len))
		echo(strs);
	else if (!ft_strncmp(*strs, "pwd", str_len))
		pwd();
	else
		return (0);
	return (1);
}
