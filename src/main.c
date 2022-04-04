#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

t_program_data	g_pd;

void	copy_env(void);
void	ft_signal(int signum);

int	main(void)
{
	extern int	rl_catch_signals;
	t_token		*head;
	char		*str;

	copy_env();
	rl_catch_signals = 0;
	//signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	signal(SIGCHLD, ft_signal);
	g_pd.dir = getcwd(g_pd.dir, 0);
	while (1)
	{
		head = token_start();
		str = readline("minishell$ ");
		if (!str)
			ft_exit(NULL);
		if (*str)
			add_history(str);
		lexer(head, str);
		ft_expand(head);
		print_tokens(head);
		ft_parse(head, STDIN_FILENO);
		ft_remove_token(head);
		free(str);
	}
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
	if (signum == SIGINT)
	{
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGCHLD)
		wait(&g_pd.last_exit_status);
}
