#include "builtins.h"

int	unset(t_env *env, char **args)
{
	t_env 	*to_unset;
	t_temp	*func;
	char	*name_only;
	int i;

	func = malloc(sizeof(t_temp));
	i = 0;
	if (!args[1])
		return (SUCCESS);
	name_only = ft_substr(args[1], 0, ft_strlen(args[1]));
	if (search_for_name_to_unset(env, name_only) == 0)
		return (0);
	to_unset = search_for_name_to_unset(env, name_only);
	free(name_only);
	if (to_unset != NULL)
	{
		if (env == to_unset)
			env = env->next;
		else
			remove_var_from_env(to_unset, env, func);
		free(func);
	}
	return(0);
}
