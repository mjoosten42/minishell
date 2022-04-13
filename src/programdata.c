#include "minishell.h"
#include "libft.h"

void	copy_env(t_program_data *pd);
void	ft_increment_shlvl(void);

t_program_data	*pd_get(void)
{
	static t_program_data	pd;

	if (pd.env)
		return (&pd);
	copy_env(&pd);
	pd.pwd = getcwd(pd.pwd, 0);
	ft_increment_shlvl();
	return (NULL);
}

int	pd_clear(void)
{
	t_program_data	*pd;
	int				exit;

	pd = pd_get();
	exit = WEXITSTATUS(pd->last_exit_status);
	ft_free_array(pd->env);
	free(pd->pwd);
	return (exit);
}

void	copy_env(t_program_data *pd)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	pd->amount_env_lines = i;
	pd->env = ft_malloc((i + 1) * sizeof(char *));
	pd->env[i] = NULL;
	while (i--)
		pd->env[i] = ft_strdup(environ[i]);
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
	add_to_env(join);
	free(join);
}
