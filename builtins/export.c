#include "builtins.h"

void	export(t_env *env, char **args)
{
	t_env *tmp;
	t_env *tmp1;
	char *var_name;
	char *var_value;

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
		var_name = check_env_string(env, args);
		var_value = return_env_value(env, args);
		//var_name = ft_substr(args[1], 0, ft_strchr(args[1], '=') - &args[1][0]);
		if (!give_variable(env, &tmp, var_name))
			ft_printf("%s\n", tmp->name);
		else
		{
			tmp1 = ft_lstnew(var_name, var_value);
			ft_lstadd_back(env, tmp1);
			printf("%s=%s\n", tmp1->name, tmp1->value);
			//print_nodes(env);
		}
	}
}
