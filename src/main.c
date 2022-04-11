#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ft_init(void);
void	copy_env(void);
void	ft_signal(int signum);
void	ft_increment_shlvl(void);

int	main(void)
{
	t_token	*head;
	char	*str;

	ft_init();
	while (1)
	{
		head = token_start();
		str = readline("minishell$ ");
		if (!str)
		{
			ft_putstr("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (*str)
		{
			add_history(str);
			ft_lexer(head, str);
			if (!ft_expand(head))
				ft_parse(head, STDIN_FILENO);
			while (head->next)
				ft_remove_token(head->next);
		}
		ft_remove_token(head);
		free(str);
	}
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
		wait(&pd->last_exit_status);
		pd->active_processes--;
	}
	if (signum == SIGQUIT && pd->active_processes)
		ft_putendl_fd("Quit: 3", 2);
}
