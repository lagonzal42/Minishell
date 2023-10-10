/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:06:11 by abasante          #+#    #+#             */
/*   Updated: 2023/10/10 13:28:35 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exit_builtin(t_env *env, char **cmd)
{
	int	a;

	a = 0;
	if (env)
		a += 1;
	if (!cmd[1])
	{
		ft_putstr_fd("exit\n", 2);
		return (0);
	}
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("pipehell: exit too many arguments\n", 2);
		return (-358);
	}
	else
	{	
		ft_putstr_fd("exit\n", 2);
		return (ft_atoi(cmd[1]));
	}
}
