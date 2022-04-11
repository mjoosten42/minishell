#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

t_program_data	g_pd;

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

	rl_event_hook = nop;
	rl_catch_signals = 0;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	signal(SIGCHLD, ft_signal);
	g_pd.pwd = getcwd(g_pd.pwd, 0);
	ft_increment_shlvl();
	copy_env();
}

void	copy_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	g_pd.amount_env_lines = i;
	g_pd.env = ft_malloc((i + 1) * sizeof(char *));
	g_pd.env[i] = NULL;
	while (i--)
		g_pd.env[i] = ft_strdup(environ[i]);
}

void	ft_signal(int signum)
{
	extern int	rl_done;

	if (signum == SIGINT)
	{
		if (g_pd.heredoc_sigint == 1)
			g_pd.heredoc_sigint = 2;
		if (g_pd.active_processes)
			ft_putchar('\n');
		rl_replace_line("", 0);
		rl_done = 1;
	}
	if (signum == SIGCHLD)
	{
		wait(&g_pd.last_exit_status);
		g_pd.active_processes--;
	}
	if (signum == SIGQUIT && g_pd.active_processes)
		ft_putendl_fd("Quit: 3", 2);
}

void	ft_increment_shlvl(void)
{
	char	*join;
	char	*str;
	int		shlvl;

	shlvl = 0;
	str = ft_get_env_from_pd("SHLVL");
	unset("SHLVL");
	if (str)
		shlvl = ft_atoi(str);
	free(str);
	str = ft_itoa(shlvl + 1);
	if (!str)
		exit(EXIT_FAILURE);
	join = ft_strjoin("SHLVL=", str);
	if (!join)
		exit(EXIT_FAILURE);
	free(str);
	export(join);
	free(join);
}
