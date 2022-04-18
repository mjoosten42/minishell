#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void    print_envs(char **envs)
{
	int i = 0;

	while (envs[i])
	{
		printf("%s\n", envs[i]);
		i++;
	}
}

void    sort(char **envs)
{
	int i = 0;
	int list_len = 4;
	// go through list
	// [c, b, d, a]
	// if (i != lastpos) strcpm(i, i+1)
	// [c, b]

	char *tmp = NULL;

	while (i != 4)
	{
		i = 0;
		if (i != list_len)
		{
			if (strcmp(envs[i], envs[i+1]) > 0)
			{
				tmp = envs[i];
				envs[i] = envs[i+1];
				envs[i+1] = tmp;
			}
			i++;
		}
		if (i == list_len) i = 0;
	}
	free(tmp);
}

int main()
{
	char **envs;

	envs = malloc(5 * sizeof(char *));

	envs[0] = "dlast";
	envs[1] = "afirst";
	envs[2] = "cthird";
	envs[3] = "bsecond";
	envs[4] = NULL;

	print_envs(envs);
	printf("\n");
	sort(envs);
	print_envs(envs);
}