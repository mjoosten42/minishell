#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

t_program_data	g_pd;

void	ft_init(void);
void	ft_signal(int signum);

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
			ft_exit(NULL);
		if (*str)
			add_history(str);
		ft_lexer(head, str);
		if (!ft_expand(head))
			ft_parse(head, STDIN_FILENO);
		while (head->next)
			ft_remove_token(head->next);
		ft_remove_token(head);
		free(str);
	}
}

int	ft_return_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (-1);
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

void	ft_init(void)
{
	extern int	rl_catch_signals;
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
	rl_catch_signals = 0;
	signal(SIGINT, ft_signal);
	signal(SIGQUIT, ft_signal);
	signal(SIGCHLD, ft_signal);
	g_pd.pwd = getcwd(g_pd.pwd, 0);
	ft_increment_shlvl();
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
	{
		wait(&g_pd.last_exit_status);
		if (WIFSIGNALED(g_pd.last_exit_status))
			ft_putchar('\n');
	}
}
