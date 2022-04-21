/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:12:25 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:12:26 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_validate(t_token *token)
{
	t_type	type;

	while (token)
	{
		type = token->type;
		if (type == red_in || type == red_out
			|| type == here_doc || type == red_out_app)
		{
			if (!token->next || token->next->type != word)
				return (ft_put_syntax_error("expected redirect target"));
			token = token->next;
		}
		if (type == pipe_char)
		{
			if (token->prev->type == start)
				return (ft_put_syntax_error("expected command before pipe"));
			if (!token->next || token->next->type == pipe_char)
				return (ft_put_syntax_error("expected command after pipe"));
		}
		token = token->next;
	}
	return (0);
}

int	ft_put_syntax_error(char *str)
{
	t_program_data	*pd;

	pd = pd_get();
	pd->last_exit_status = 2;
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}
