#include "execution.h"

int	main(int ac, char **av, char **envp)
{
	int i;
	int j;
	int a;
	char	**split_cmd;
	char	**bin_paths;
	char 	*holder;

	i = 0;
	j = 0;
	a = 1;
	if (!av[1])
		exit(0);
	if (check_if_path_absolute(av[1]) == 0)
		execute_commands_path(av[1], &av[1], envp);
	t_env *env;

	env = get_env(envp, env);
	split_cmd = ft_split(av[1], ' ');
	while (env && env->name && ft_strncmp(env->name, "PATH", 4) != 0)
		env = env->next;
	bin_paths = ft_split(env->value, ':');
	// while (bin_paths[i])
	// 	printf("%s\n", bin_paths[i++]);
	while (bin_paths[j] && a == 1)
	{
		holder = ft_strjoin(ft_strjoin(bin_paths[j], "/"), split_cmd[i]);
		j++;
		a = check_if_access(holder);
		if (a == 1)
			free(holder);
	}
	if (a == 0)
		execute_commands_path(holder, &av[1], envp);
	else
		ft_putstr_fd("Minishell: command not found", STDERR_FILENO);
	free(split_cmd);
	free(bin_paths);
}


void	redirections()
{

}
