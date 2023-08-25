/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:07:46 by abasante          #+#    #+#             */
/*   Updated: 2023/08/25 18:31:04 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	check_env_string(t_env *env, char **args)
{
	int i;
	i = 0;
	while (args[1][i] != '=')
	{
		if (ft_isalnum(args[1][i]) == 0 && args[1][i] != '_')
			ft_printf("error\n");
		i++;
		ft_printf("esta bien\n");		
	}
	while(args[1][i] && !ft_is_space(args[1][i]))
		i++;
}

void	check_if_already_exists(t_env *env, char **args)
{
				
}
