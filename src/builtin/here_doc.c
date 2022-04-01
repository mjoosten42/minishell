#include "minishell.h"
#include "libft.h"
#include <fcntl.h>

void	ft_here_doc(t_token **head)
{
	char *end_doc;
	char *str;
	char *temp;
	char *join_str;

	if ((*head)->next->type == space)
		ft_remove_token((*head)->next);
	end_doc = (*head)->next->value;
	str = ft_strdup("");
	// int fd = open("testfile.txt", O_RDONLY);
	while (str)
	{
		ft_putstr("> ");
		temp = str;
		str = ft_get_next_line(STDIN_FILENO);
		if (!str)
			break ;
		if (!ft_strncmp(end_doc, str, ft_strlen(end_doc)))
			break ;
		join_str = ft_strjoin(temp, str);
		free(str);
		free(temp);
		str = join_str;
	}
	free((*head)->value);
	(*head)->value = join_str;
	ft_remove_token((*head)->next);
}
