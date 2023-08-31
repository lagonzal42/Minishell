#include "builtins.h"

void	unset(t_env *env, char **args)
{
	t_env *to_unset;
	char	*name_only;
	int i;

	i = 0;
	if (!args[1])
		exit (ERROR);
	while (args[1][i] != '=')
		i++;
	name_only = ft_substr(args[1], 0, i);
	to_unset = search_for_name_to_unset(env, name_only);
	if (to_unset != NULL)
	{
		printf("%s=%s\n", to_unset->name, to_unset->value);
	}
	else
		printf("there is no %s name variable\n", name_only);
}
