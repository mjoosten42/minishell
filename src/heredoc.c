/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:11:07 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:11:15 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_heredoc_loop(t_program_data *pd, char *end);

int	ft_here_doc(t_token *token, int *fd)
{
	t_program_data	*pd;

	pd = pd_get();
	token = token->prev;
	ft_remove_token(token->next);
	token = token->next;
	if (*fd > STDERR_FILENO)
		ft_close(*fd);
	pd->heredoc_sigint = 1;
	*fd = ft_heredoc_loop(pd, token->value);
	pd->heredoc_sigint = 0;
	if (*fd < 0)
		return (-1);
	ft_remove_token(token);
	return (0);
}

int	ft_heredoc_loop(t_program_data *pd, char *end)
{
	char	*str;
	int		fds[2];
	int		len;

	ft_pipe(fds);
	len = ft_strlen(end);
	while (1)
	{
		str = ft_read("> ");
		if (pd->heredoc_sigint == 2)
		{
			free(str);
			ft_close(fds[0]);
			ft_close(fds[1]);
			return (-1);
		}
		if (!str || !ft_strncmp(str, end, len + 1))
			break ;
		write(fds[1], str, ft_strlen(str));
		write(fds[1], "\n", 1);
		free(str);
	}
	ft_close(fds[1]);
	return (fds[0]);
}
