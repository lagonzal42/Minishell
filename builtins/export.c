#include "builtins.h"

void	export(t_env *env, char **args)
{
	t_env *tmp;

	tmp = env;
	//Si solo nos viene un argumento, "export" a secas, escribimos todas las variables del enviroment con "declare -x" enfrente.
	if (!args[1])
	{
		while (tmp != NULL)
		{
			ft_printf("declare -x %s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		check_env_string(env, args);
		//dcheck_if_already_exits(env, args);
	}
}
