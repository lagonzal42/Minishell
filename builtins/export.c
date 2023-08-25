#include "builtins.h"

void	export(t_env *env, char **args)
{
	t_env *tmp;
	char *var_name;

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
		var_name = ft_substr(args[1], 0, ft_strchr(args[1], '=')- &args[1][0]);
		if (!give_variable(env, &tmp, var_name))
			printf("%s\n", tmp->name);
		//else

		//check_if_already_exits(env, args, var_name);
	}
}
