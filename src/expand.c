#include "minishell.h"
#include "libft.h"

void	ft_join_words(t_token *token);
void	ft_expand_dollar(t_token *token);
int		ft_expand_quotes(t_token *token, t_type type);

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
		if (error)
			return (error);
		token = token->next;
	}
	ft_join_words(head);
	return (0);
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
		if (type == space || type == tab)
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
		return (ft_return_error("Syntax error: solo (d)quote"));
	while (token->next->type != type)
	{
		if (type == dquote && token->next->type == dollar)
			ft_expand_dollar(token->next);
		tmp = token->value;
		token->value = ft_strjoin(token->value, token->next->value);
		free(tmp);
		ft_remove_token(token->next);
		if (!token->next)
			return (ft_return_error("Syntax error: solo (d)quote"));
	}
	ft_remove_token(token->next);
	return (0);
}

//	Temporary: $$ expands to pid
int	expand_$$(t_token *token)
{
	if (!ft_strncmp(token->value, "$", 2)
	&& token->next && token->next->type == dollar
	&& !ft_strncmp(token->next->value, "$", 2))
	{
		free(token->value);
		token->value = ft_itoa(getpid());
		ft_remove_token(token->next);
		return (1);
	}
	return (0);
}

void	ft_expand_dollar(t_token *token)
{
	t_program_data	*pd;
	char		*str;

	pd = pd_get();
	token->type = word;
	if (expand_$$(token))
		return ;
	else if (token->value[1] == '?')
	{
		free(token->value);
		token->value = ft_itoa(WEXITSTATUS(pd->last_exit_status));
	}
	else if (token->value[1])
	{
		str = ft_get_env_from_pd(&token->value[1]);
		if (!str)
			token->type = space;
		free(token->value);
		token->value = str;
	}
	if (token->next && token->next->type == word)
	{
		str = token->value;
		token->value = ft_strjoin(str, token->next->value);
		free(str);
		ft_remove_token(token->next);
	}
}

char	*ft_get_env_from_pd(char *str)
{
	t_program_data	*pd;
	char			*tmp;
	int				len;
	int				i;

	i = 0;
	pd = pd_get();
	tmp = ft_strjoin(str, "=");
	len = ft_strlen(tmp);
	while (pd->env[i] && ft_strncmp(pd->env[i], tmp, len))
		i++;
	free(tmp);
	if (!pd->env[i])
		return (NULL);
	len = 0;
	while (pd->env[i][len] != '=')
		len++;
	return (ft_substr(pd->env[i], len + 1, ft_strlen(pd->env[i]) - len));
}
