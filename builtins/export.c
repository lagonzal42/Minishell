#include "builtins.h"

void	export(t_env *env, char **args)
{
	t_env *tmp;

	tmp = env;
	//print_nodes(env);
	if (!args[1])
	{
		while (tmp != NULL)
		{
			printf("declare -x %s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		int i;

		i = 0;
		while (args[1][i] != '=')
		{
			if (check_var_name(args[1][i]) != 0)
			{
				printf("error\n");
			}
			i++;
			printf("esta bien\n");		
		}
	}
}

int		check_var_name(char arg)
{
	if ((arg >= 'a' && arg <= 'z') && \
	(arg >= 'A' && arg <= 'Z') && \
	(arg >= '0' && arg <= '9') && \
	arg == '_')
		return (0);
	return (1);
}
