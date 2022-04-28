/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:11:03 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:12:48 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_join_words(t_token *token);
void	ft_expand_dollar(t_token *token);
int		ft_expand_quotes(t_token *token, t_type type);
void	ft_check(t_token *token);

int	ft_expand(t_token *head)
{
	t_token	*token;
	t_type	type;
	int		error;

	error = 0;
	token = head;
	while (token)
	{
		type = token->type;
		if (type == quote)
			error = ft_expand_quotes(token, quote);
		if (type == dquote)
			error = ft_expand_quotes(token, dquote);
		if (type == dollar)
			ft_expand_dollar(token);
		if (type == here_doc)
			ft_check(token);
		if (error)
			return (error);
		token = token->next;
	}
	ft_join_words(head);
	return (0);
}

void	ft_check(t_token *token)
{
	if (token->next && token->next->type == dollar)
		token->next->type = word;
	if (token->next && token->next->type == space
		&& token->next->next && token->next->next->type == dollar)
		token->next->next->type = word;
}

void	ft_join_words(t_token *token)
{
	t_type	type;
	char	*tmp;

	while (token)
	{
		type = token->type;
		if (type == word && token->next && token->next->type == word)
		{
			tmp = token->value;
			token->value = ft_strjoin(tmp, token->next->value);
			free(tmp);
			ft_remove_token(token->next);
			token = token->prev;
		}
		if (type == space || type == tab || type == newline)
		{
			token = token->prev;
			ft_remove_token(token->next);
		}
		token = token->next;
	}
}

int	ft_expand_quotes(t_token *token, t_type type)
{
	char	*tmp;

	token->type = word;
	free(token->value);
	token->value = ft_strdup("");
	if (!token->next)
		return (ft_put_syntax_error("solo (d)quote"));
	while (token->next->type != type)
	{
		if (type == dquote && token->next->type == dollar)
			ft_expand_dollar(token->next);
		tmp = token->value;
		token->value = ft_strjoin(token->value, token->next->value);
		free(tmp);
		ft_remove_token(token->next);
		if (!token->next)
			return (ft_put_syntax_error("solo (d)quote"));
	}
	ft_remove_token(token->next);
	return (0);
}

void	ft_expand_dollar(t_token *token)
{
	t_program_data	*pd;
	char			*str;

	pd = pd_get();
	token->type = word;
	if (token->value[1] == '?')
	{
		free(token->value);
		token->value = ft_itoa(pd->last_exit_status);
	}
	else if (token->value[1])
	{
		str = ft_get_env_from_pd(&token->value[1]);
		free(token->value);
		token->value = str;
		if (!str)
			token->value = ft_strdup("");
	}
	if (token->next && token->next->type == word)
	{
		str = token->value;
		token->value = ft_strjoin(str, token->next->value);
		free(str);
		ft_remove_token(token->next);
	}
}
