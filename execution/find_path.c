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
	check_if_path_absolute(av);
	split_cmd = ft_split(av[1], ' ');

	if (!split_cmd)
		return (0);
	i = 0;
	while (split_cmd[i])
		printf("%s\n", split_cmd[i++]);
	printf("---------------------------\n");
	while (env && env->name && ft_strncmp(env->name, "PATH", 4) != 0)
		env = env->next;
	printf("%s=%s\n", env->name, env->value);
	printf("---------------------------\n");
	bin_paths = ft_split(env->value, ':');
	j = 0;
	while (bin_paths[j])
		printf("%s\n", bin_paths[j++]);
	i = 0;
	j = 0;
	while (bin_paths[j])
	{
		holder = ft_strjoin(ft_strjoin(bin_paths[j], "/"), split_cmd[i]);
		j++;
		printf("%s\n", holder);
	}
}
