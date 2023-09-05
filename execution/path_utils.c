#include "execution.h"

int	check_if_path_absolute(char *cmd)
{
	if (cmd[0] == '/')
		return (0);
	else
		return (1);
}

void	execute_commands_path(char *path_name, char **av, char **envp)
{
	printf("entro aqui\n");
	if(execve(path_name, av, envp) == -1)
		printf("no se ha podido ejecutar el comando %s\n", path_name);
	printf("si funciona esto no deberia printearse\n");
}
