#include "minishell.h"
#include "libft.h"

void	ft_expand_dollar(t_token *token);
int		ft_expand_quotes(t_token *token, enum e_symbol type);

int	ft_expand(t_token *head)
{
	t_token	*token;
	int		error;
	int		type;

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
	token = head;
	while (token)
	{
		if (token->type == space || token->type == tab)
		{
			token = token->prev;
			ft_remove_token(token->next);
		}
		token = token->next;
	}
	return (0);
}

int	ft_expand_quotes(t_token *token, enum e_symbol type)
{
	char	*tmp;

	token->type = word;
	free(token->value);
	if (token->prev->type == word)
	{
		token->value = ft_strdup(token->prev->value);
		ft_remove_token(token->prev);
	}
	else
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
	if (token->next->type == word)
	{
		tmp = token->value;
		token->value = ft_strjoin(token->value, token->next->value);
		free(tmp);
		ft_remove_token(token->next);
	}
	return (0);
}

void	ft_expand_dollar(t_token *token)
{
	char	*str;

	print_tokens(token);
	token->type = word;
	if (token->next && token->next->type == dollar)
		ft_expand_dollar(token->next);
	//	Temporary: $$ expands to pid
	if (token->next && token->next->type == dollar && !ft_strncmp(token->value, "$", 2))
	{
		free(token->value);
		token->value = ft_itoa(getpid());
		ft_remove_token(token->next);
	}
	else if (token->value[1] == '?')
	{
		free(token->value);
		token->value = ft_itoa(WEXITSTATUS(g_pd.last_exit_status));
	}
	else if (token->value[1])
	{
		str = ft_get_env_from_pd(&token->value[1]);
		if (!str)
			str = ft_strdup("");
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
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = ft_strjoin(str, "=");
	len = ft_strlen(tmp);
	while (g_pd.env[i] && ft_strncmp(g_pd.env[i], tmp, len))
		i++;
	free(tmp);
	if (!g_pd.env[i])
		return (NULL);
	len = 0;
	while (g_pd.env[i][len] != '=')
		len++;
	return (ft_substr(g_pd.env[i], len + 1, ft_strlen(g_pd.env[i]) - len));
}
