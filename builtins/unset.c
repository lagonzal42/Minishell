#include "builtins.h"

void	unset(t_env *env, char **args)
{
	t_env 	*to_unset;
	t_temp	*func;
	char	*name_only;
	int i;

	func = malloc(sizeof(t_temp));
	i = 0;
	if (!args[1])
		exit (SUCCESS);
	while (args[1][i] != '=')
		i++;
	name_only = ft_substr(args[1], 0, i);
	to_unset = search_for_name_to_unset(env, name_only);
	if (to_unset != NULL)
	{
		if (env == to_unset)
			env = env->next;
		else
			remove_var_from_env(to_unset, env, func);
		//print_nodes(env);
		free(func);
	}
	exit(0);
}
