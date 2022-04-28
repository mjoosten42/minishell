/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:10:27 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:46:18 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_token	*token_start(void)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	token->next = NULL;
	token->prev = NULL;
	token->value = NULL;
	token->type = start;
	return (token);
}

int	token_add_back(t_token *token, t_token *new_token)
{
	while (token->next)
		token = token->next;
	token->next = new_token;
	new_token->prev = token;
	new_token->next = NULL;
	return (ft_strlen(new_token->value));
}

void	ft_remove_token(t_token *token)
{
	if (!token)
		return ;
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free(token->value);
	free(token);
}
