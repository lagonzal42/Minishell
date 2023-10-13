/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:06:11 by abasante          #+#    #+#             */
/*   Updated: 2023/10/13 16:03:44 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	numeric_argument(char *arg)
{
	int	n;

	n = 0;
	while (arg[n])
	{
		if (ft_isdigit(arg[n]))
			n++;
		else
			return (1);
	}
	return (0);
}

int	exit_builtin(t_env *env, char **cmd)
{
	env = (t_env *)env;
	if (cmd[1] && numeric_argument(cmd[1]))
	{
		ft_putstr_fd("exit\npipehell: exit: asdf: numeric argument required\n"\
					, 2);
		return (255);
	}
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
