#include "minishell.h"
#include "libft.h"

void	ft_expand_dollar(t_token *token);
int		ft_expand_quotes(t_token *token, enum e_symbol type);

int	ft_expand(t_token *token)
{
	int	error;
	int	type;

	error = 0;
	while (token)
	{
		type = token->type;
		if (type == quote)
			error = ft_expand_quotes(token, quote);
		if (type == dquote)
			error = ft_expand_quotes(token, dquote);
		if (type == dollar)
			ft_expand_dollar(token);
		if (type == space || type == tab)
		{
			token = token->prev;
			ft_remove_token(token->next);
		}
		if (error)
			return (error);
		token = token->next;
	}
	return (0);
}

int	ft_expand_quotes(t_token *token, enum e_symbol type)
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

void	ft_expand_dollar(t_token *token)
{
	t_token	*next;
	char	*str;

	next = token->next;
	token->type = word;
	free(token->value);
	//	Temporary: $$ expands to pid
	if (next && next->type == dollar)
	{
		token->value = ft_itoa(getpid());
		ft_remove_token(next);
		return ;
	}
	if (next && next->type == word)
	{
		if (next->value[0] == '?')
		{
			token->value = ft_itoa(WEXITSTATUS(g_pd.last_exit_status));
			if (next->value[1])
			{
				str = ft_strjoin(token->value, &next->value[1]);
				free(token->value);
				token->value = str;
			}
		}
		else
			token->value = ft_get_env_from_pd(next->value);
		ft_remove_token(next);
	}
	else
		token->value = ft_strdup("$");
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
		return (ft_strdup(""));
	len = 0;
	while (g_pd.env[i][len] != '=')
		len++;
	return (ft_substr(g_pd.env[i], len + 1, ft_strlen(g_pd.env[i])));
}
