
#include "builtins.h"

// int pwd()
// {
// 	char cwd[1000000];

// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 		printf("%s\n", getcwd(cwd, sizeof(cwd)));
// 	else
// 	{
// 		perror("getcwd() error");
// 		exit (1);
// 	}
// 	exit (0);
// }

void	pwd(t_env *env, char **cmd)
{
	char	*test;
	env = 0;

	test = getcwd(NULL, 0);
	if (test == NULL || cmd[1])
		ft_putstr_fd("Error in pwd\n", 1);
	else
	{
		ft_putstr_fd(test, 1);
		write(1, "\n", 1);
	}
}
