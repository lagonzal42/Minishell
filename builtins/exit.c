/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:06:11 by abasante          #+#    #+#             */
/*   Updated: 2023/09/27 13:06:13 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exit_builtin(t_env *env, char **cmd)
{
	env = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("exit\nminishell: exit tooo many arguments", 2);
		exit (1);
	}
	ft_putstr_fd("exit\n", 2);
	exit(ft_atoi(cmd[1]));
}
