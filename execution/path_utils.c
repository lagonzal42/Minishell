#include "execution.h"

int	check_if_path_absolute(char *cmd)
{
	if (cmd[0] == '/')
		return (0);
	else
		return (1);
}

int	execute_commands_path(char *path_name, char **av, char **envp)
{
	if(execve(path_name, av, envp) == -1)
		return (0);
	printf("si funciona esto no deberia printearse\n");
	return 0;
}
