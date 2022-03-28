#include "minishell.h"
#include "libft.h"
#include "fcntl.h"

void	ft_expand(t_token **head);
void	ft_expand_dollar(t_token *token);
void	ft_expand_quotes(t_token *token, enum e_symbol type);
void	ft_remove_token(t_token *head);
void	ft_get_fd0(t_token **head, int *fd0);
int		ft_get_fd1(t_token **head, int *fd1);
char	**ft_get_args(t_token **head);

void	ft_parse(t_token **head, int pipefd)
{
	pid_t	pid;
	char	**strs;
	char	*path;
	int		fds[2];
	int		pipe_read;
	int		exit_status;

	fds[0] = pipefd;
	fds[1] = 1;
	print_tokens(*head);
	ft_get_fd0(head, &fds[0]);
	pipe_read = ft_get_fd1(head, &fds[1]);
	strs = ft_get_args(head);
	print_tokens(*head);
	if (is_builtin(strs))
		return ;
	path = ft_getpath(*strs);
	if (!path)
		return ;
	pid = ft_exec(path, strs, fds);
	ft_free_array(strs);
	free(path);
	if (pipe_read)
	{
		ft_parse(&(*head)->next, pipe_read);
		ft_remove_token(*head);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		g_pd.last_exit_status = WEXITSTATUS(exit_status);
	}
}

void	ft_get_fd0(t_token **head, int *fd0)
{
	t_token	*token;

	token = *head;
	while (token && token->type != pipe_char)
	{
		if (token->type == red_in && token->next->type == word)
		{
			*fd0 = open(token->next->value, O_RDONLY);
			if (*fd0 < 0)
				perror("Error opening file:");
			if (token == *head)
				*head = token->next->next;
			ft_remove_token(token);
			ft_remove_token(token->next);
		}
		token = token->next;
	}
}

//	Look for > and >> tokens, get fd with open() and remove the token.
//	If followed by a pipe, make a pipe and return the read end.
int	ft_get_fd1(t_token **head, int *fd1)
{
	t_token	*token;
	int		pipefds[2];

	token = *head;
	while (token && token->type != pipe_char)
	{
		if ((token->type == red_out || token->type == red_out_app)
			&& token->next->type == word)
		{
			if (token == *head)
				*head = token->next->next;
			if (token->type == red_out)
				*fd1 = open(token->next->value, O_CREAT | O_WRONLY, 0644);
			else
				*fd1 = open(token->next->value,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			ft_remove_token(token);
			ft_remove_token(token->next);
		}
		token = token->next;
	}
	if (!token)
		return (0);
	pipe(pipefds);
	*fd1 = pipefds[1];
	return (pipefds[0]);
}

char	**ft_get_args(t_token **head)
{
	t_token	*token;
	t_token	*prev;
	char	**strs;
	int		i;

	i = 0;
	token = *head;
	prev = token;
	while (token && token->type != pipe_char)
	{
		i++;
		prev = token;
		token = token->next;
	}
	token = prev;
	if (token)
		*head = token->next;
	strs = ft_malloc(sizeof(*strs) * (i + 1));
	strs[i] = NULL;
	while (i--)
	{
		prev = token->prev;
		strs[i] = ft_strdup(token->value);
		ft_remove_token(token);
		token = prev;
	}
	return (strs);
}

void	ft_expand(t_token **head)
{
	t_token	*ptr;
	t_token	*next;

	ptr = *head;
	while (ptr)
	{
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

void	ft_expand_dollar(t_token *token)
{
	token->type = word;
	free(token->value);
	if (token->next && token->next->type == word)
	{
		if (!ft_strncmp(token->next->value, "?", 1))
			token->value = ft_itoa(g_pd.last_exit_status);
		else
			token->value = ft_get_env_from_pd(token->next->value);
		ft_remove_token(token->next);
	}
	else
		token->value = ft_strdup("$");
}

/**
 * if input has qoutes go through list to match qoutes
 * merge value of block in between qoutes
 * 
 * remove blocks
 * 
 * Edit: set first (d)quote to empty string with type word
 * then keep joining until (d)quote is reached.
 */
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

void	ft_remove_token(t_token *token)
{
	t_token	*prev;
	t_token	*next;

	if (!token)
		return ;
	prev = token->prev;
	next = token->next;
	free(token->value);
	free(token);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}
