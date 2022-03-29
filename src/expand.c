#include "minishell.h"
#include "libft.h"

void	ft_expand_quotes(t_token *token, enum e_symbol type);
void	ft_expand_dollar(t_token *token);
char	*ft_get_env_from_pd(char *str);
int		ft_isnumber(char *str);

void	ft_expand(t_token **head)
{
	t_token	*ptr;
	t_token	*next;

	ptr = *head;
	while (ptr)
	{
		if (ptr->type == word && ft_isnumber(ptr->value))
			if (ptr->next && ptr->next->type == red_out)
				ptr->type = file_descriptor;
		if (ptr->type == quote)
			ft_expand_quotes(ptr, quote);
		else if (ptr->type == dquote)
			ft_expand_quotes(ptr, dquote);
		else if (ptr->type == dollar)
			ft_expand_dollar(ptr);
		else if (ptr->type == space)
		{
			next = ptr->next;
			ft_remove_token(ptr);
			if (ptr == *head)
				*head = next;
			ptr = next;
		}
		else
			ptr = ptr->next;
	}
}

void	ft_expand_quotes(t_token *token, enum e_symbol type)
{
	char	*tmp;

	token->type = word;
	free(token->value);
	token->value = ft_strdup("");
	if (!token->next)
		ft_error("Error: solo (d)quote");
	while (token->next->type != type)
	{
		if (type == dquote && token->next->type == dollar)
			ft_expand_dollar(token->next);
		tmp = token->value;
		token->value = ft_strjoin(token->value, token->next->value);
		free(tmp);
		ft_remove_token(token->next);
		if (!token->next)
			ft_error("Error: solo (d)quote");
	}
	ft_remove_token(token->next);
}

void	ft_expand_dollar(t_token *token)
{
	char	*str;

	token->type = word;
	free(token->value);
	if (token->next && token->next->type == word)
	{
		if (token->next->value[0] == '?')
		{
			token->value = ft_itoa(WEXITSTATUS(g_pd.last_exit_status));
			if (token->next->value[1])
			{
				str = ft_strjoin(token->value, &token->next->value[1]);
				free(token->value);
				token->value = str;
			}
		}
		else
			token->value = ft_get_env_from_pd(token->next->value);
		ft_remove_token(token->next);
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
	if (!g_pd.env[i])
		return (ft_strdup(""));
	return (ft_strdup(g_pd.env[i]));
}

int	ft_isnumber(char *str)
{
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}
