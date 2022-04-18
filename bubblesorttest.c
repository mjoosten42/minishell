#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	print_envs(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		printf("declare -x %s\n", envs[i]);
		i++;
	}
}

int	get_env_len(char **envs)
{
	int i = 0;
	while (envs[i])
		i++;
	return (i);
}

int	is_sorted(char **envs)
{
	int i = 0;

	while (envs[i])
	{
		if (envs[i + 1] != NULL)
			if (strcmp(envs[i], envs[i+1]) > 0)
				return (0);
		i++;
	}
	return (1);
}

void	sort(char **envs)
{
	int		i;
	int		env_len;
	char	*tmp;

	env_len = get_env_len(envs);
	while (is_sorted(envs) == 0)
	{
		i = 0;
		while (i < env_len - 1)
		{
			if (strcmp(envs[i], envs[i+1]) > 0)
			{
				tmp = envs[i];
				envs[i] = envs[i+1];
				envs[i+1] = tmp;
			}
			i++;
		}
	}
}

int main(int argc, char **argv, char **envs)
{
	(void)argc;
	(void)argv;
	sort(envs);
	print_envs(envs);
}