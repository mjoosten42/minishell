#include "minishell.h"
#include "libft.h"
#include "fcntl.h"

#define MODE 0644

int		ft_get_fds(t_token **head, int fds[2]);
char	**ft_get_args(t_token **head);
int		ft_argsize(t_token *token);

void	ft_parse(t_token **head, int pipefd)
{
	pid_t	pid;
	char	**strs;
	int		fds[2];

	if (!*head)
		return(ft_putendl_fd("Pipe into nothing", 2));
	fds[0] = pipefd;
	fds[1] = STDOUT_FILENO;
	pipefd = ft_get_fds(head, fds);
	strs = ft_get_args(head);
	pid = ft_exec(strs, fds);
	ft_free_array(strs);
	if (pipefd)
		ft_parse(head, pipefd);
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
	int		type;

	token = *head;
	while (token)
	{
		type = token->type;
		if (type == pipe_char)
		{
			pipe(pipefds);
			fds[1] = pipefds[1];
			return (pipefds[0]);
		}
		if (type == heredoc)
		{
			fds[0] = ft_atoi(token->value);
			if (token == *head)
				*head = token->next;
			ft_remove_token(token);
		}
		if ((type == red_out || type == red_out_app)
			&& token->next->type == word)
		{
			if (token == *head)
				*head = token->next->next;
			if (type == red_out)
				fds[1] = ft_open(token->next->value, O_CREAT | O_WRONLY, MODE);
			else
				fds[1] = ft_open(token->next->value,
						O_CREAT | O_WRONLY | O_APPEND, MODE);
			if (fds[1] < 0)
				perror(token->next->value);
			ft_remove_token(token);
			ft_remove_token(token->next);
		}
		if (type == red_in && token->next->type == word)
		{
			fds[0] = ft_open(token->next->value, O_RDONLY, MODE);
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

int	ft_argsize(t_token *token)
{
	int	size;

	size = 0;
	while (token && token->type != pipe_char)
	{
		size++;
		token = token->next;
	}
	return (size);
}

char	**ft_get_args(t_token **head)
{
	t_token	*next;
	char	**strs;
	int		size;
	int		i;

	i = 0;
	size = ft_argsize(*head);
	strs = ft_malloc(sizeof(*strs) * (size + 1));
	strs[size] = NULL;
	while (i < size)
	{
		next = (*head)->next;
		strs[i] = ft_strdup((*head)->value);
		ft_remove_token(*head);
		*head = next;
		i++;
	}
	if (*head && (*head)->type == pipe_char)
	{
		next = (*head)->next;
		ft_remove_token(*head);
		*head = next;
	}
	return (strs);
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
