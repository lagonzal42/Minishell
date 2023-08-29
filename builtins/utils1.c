/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:07:46 by abasante          #+#    #+#             */
/*   Updated: 2023/08/25 19:00:56 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*check_env_string(t_env *env, char **args)
{
	char	*var_name;
	int i;
	int a;
	i = 0;
	while (args[1][i] != '=')
	{
		if (ft_isalnum(args[1][i]) == 0 && args[1][i] != '_')
			ft_printf("error\n");
		i++;
		ft_printf("esta bien\n");		
	}
	a = i;
	while(args[1][i] && !ft_is_space(args[1][i]))
		i++;
	var_name = ft_substr(args[1], 0, a);
	return (var_name);
}

// void	check_if_already_exists(t_env *env, char **args, char *var_name)
// {
// 	t_env	*to_name_if_exists;
// 	to_name_if_exists = give_variable(env, var_name);
	
// }
