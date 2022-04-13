#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ft_init(void);
void	ft_signal(int signum);

int	main(void)
{
	t_token	*head;
	char	*str;

	ft_init();
	head = token_start();
	while (1)
	{
		str = ft_read("minishell$ ");
		if (!str)
			break ;
		ft_lexer(head, str);
		if (*str)
			add_history(str);
		if (!ft_expand(head))
			if (!ft_validate(head))
				ft_parse(head, STDIN_FILENO);
		while (head->next)
			ft_remove_token(head->next);
		free(str);
	}
	rl_clear_history();
	if (isatty(STDIN_FILENO))
		ft_putstr("exit\n");
	return (pd_clear());
}

void	ft_init(void)
{
	extern int	(*rl_event_hook)(void);
	extern int	rl_catch_signals;

	pd_get();
	rl_event_hook = nop;
	rl_catch_signals = 0;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	signal(SIGCHLD, ft_signal);
}

void	ft_signal(int signum)
{
	t_program_data	*pd;
	extern int		rl_done;
	int				exit;

	pd = pd_get();
	if (signum == SIGINT)
	{
		if (pd->heredoc_sigint == 1)
			pd->heredoc_sigint = 2;
		if (pd->active_processes)
			ft_putchar('\n');
		rl_replace_line("", 0);
		rl_done = 1;
	}
	if (signum == SIGCHLD)
	{
		wait(&exit);
		pd->last_exit_status = WEXITSTATUS(exit);
		pd->active_processes--;
	}
	if (signum == SIGQUIT && pd->active_processes)
		ft_putendl_fd("Quit: 3", 2);
}

char	*ft_read(char *prompt)
{
	char	*str;
	int		len;

	if (isatty(STDIN_FILENO))
		return (readline(prompt));
	str = ft_get_next_line(STDIN_FILENO);
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = 0;
	return (str);
}
