#include "builtins.h"

t_env	*search_for_name_to_unset(t_env *env, char *search)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, search) == 0)
			return(tmp);
		tmp = tmp->next;
	}
	return 0;
}