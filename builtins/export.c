#include "builtins.h"

//Si solo nos viene un argumento, "export" a secas, escribimos 
//todas las variables del enviroment con "declare -x" enfrente.
int	export(t_env *env, char **args)
{
	t_env *tmp;
	char *var_name;
	char *var_value;

	tmp = env;
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
		var_name = check_env_string(args);
		var_value = return_env_value(args);
		if (!give_variable(env, &tmp, var_name))
		{
			free(tmp->value);
			tmp->value = var_value;
			free(var_name);
		}
		else
		{
			tmp = ft_lstnew(var_name, var_value);
			ft_lstadd_back(env, tmp);
		}
	}
	return (0);
}
