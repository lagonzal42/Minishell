#include "execution.h"

int main(int ac, char **av, char **envp)
{
	t_env	*env;
	int i;
	int j;
	char	**split_cmd;
	char	**bin_paths;
	char 	*holder;

	env = get_env(envp, env);
	if (!av[1])
	{
		printf("error: no has metido ningun comando\n");
		exit(0);
	}
	if (check_if_path_absolute(av[1]) == 0)
	{
		av[2] = NULL;
		execute_commands_path(av[1], av, envp);
	}
	split_cmd = ft_split(av[1], ' ');
	i = 0;
	while (split_cmd[i])
		printf("%s\n", split_cmd[i++]);
	while (env && env->name && ft_strncmp(env->name, "PATH", 4) != 0)
		env = env->next;
	printf("---------------------------\n");
	bin_paths = ft_split(env->value, ':');
	j = 0;
	while (bin_paths[j])
		printf("%s\n", bin_paths[j++]);
	i = 0;
	j = 0;
	printf("---------------------------\n");
	while (bin_paths[j])
	{
		holder = ft_strjoin(ft_strjoin(bin_paths[j], "/"), split_cmd[i]);
		j++;
		printf("%s\n", holder);
		execute_commands_path(holder, av, envp);
	}
}

// int main(int ac, char **envp)
// {
// 	char	pathname[] = "/bin/ls";
// 	char	*argv[] = {"ls", NULL};
// 	//char	*envp[] = {NULL};


// 	if(execve(pathname, argv, envp) == -1)
// 		printf("no se ha podido ejecutar el comando %s\n", pathname);
// 	printf("si funciona esto no deberia printearse\n");
// }