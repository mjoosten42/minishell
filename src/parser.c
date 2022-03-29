#include "minishell.h"
#include "libft.h"
#include "fcntl.h"

int		ft_get_fds(t_token **head, int fds[2]);
char	**ft_get_args(t_token **head);

void	ft_parse(t_token **head, int pipefd)
{
	pid_t	pid;
	char	**strs;
	int		fds[3];

	fds[0] = pipefd;
	fds[1] = STDOUT_FILENO;
	fds[2] = ft_get_fds(head, fds);
	strs = ft_get_args(head);
	pid = ft_exec(strs, fds);
	ft_free_array(strs);
	if (fds[2])
	{
		while ((*head)->type != pipe_char)
			*head = (*head)->next;
		ft_parse(&(*head)->next, fds[2]);
		ft_remove_token(*head);
	}
	else
	{
		signal(SIGCHLD, NULL);
		waitpid(pid, &g_pd.last_exit_status, 0);
	}
}

int	ft_get_fds(t_token **head, int fds[2])
{
	t_token	*token;
	int		pipefds[2];

	token = *head;
	while (token)
	{
		if (token->type == pipe_char)
		{
			pipe(pipefds);
			fds[1] = pipefds[1];
			return (pipefds[0]);
		}
		if ((token->type == red_out || token->type == red_out_app)
			&& token->next->type == word)
		{
			if (token == *head)
				*head = token->next->next;
			if (token->type == red_out)
				fds[1] = open(token->next->value, O_CREAT | O_WRONLY, 0644);
			else
				fds[1] = open(token->next->value,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fds[1] < 0)
				perror(token->next->value);
			ft_remove_token(token);
			ft_remove_token(token->next);
		}
		if (token->type == red_in && token->next->type == word)
		{
			fds[0] = open(token->next->value, O_RDONLY);
			if (fds[0] < 0)
				perror(token->next->value);
			if (token == *head)
				*head = token->next->next;
			ft_remove_token(token);
			ft_remove_token(token->next);
		}
		token = token->next;
	}
	return (0);
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
