#include "execution.h"


//this function finds the path to be executed when the command isn't written
//with the absolute path, it also checks if it has access to that path to then execute 
//the command with execve outside this function

/*if int bon is 1, it means it is a built in function, so in this case we don't
  need to find the path of the command because we are going to execute it with our code.
*/
char	*find_path(int bon, t_cmnd **node, t_env *env)
{
	int i;
	int j;
	int a;
	char	**bin_paths;
	char 	*holder;

	i = 0;
	j = 0;
	a = 1;
	if (bon == 1)
		execute_builtins(node, env);
	if (!(*node)->cmd[0])
		exit(0);
	while (env && env->name && ft_strncmp(env->name, "PATH", 4) != 0)
		env = env->next;
	bin_paths = ft_split(env->value, ':');
	while (bin_paths[j] && a == 1)
	{
		holder = ft_strjoin(ft_strjoin(bin_paths[j], "/"), (*node)->cmd[0]);
		j++;
		a = check_if_access(holder);
		if (a == 1)
			free(holder);
	}
	return (holder);
	free(bin_paths);
}
