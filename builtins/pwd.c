/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:10:53 by abasante          #+#    #+#             */
/*   Updated: 2023/10/13 17:10:03 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(t_env *env, char **cmd)
{
	char	*test;

	cmd = (char **)cmd;
	env = (t_env *)env;
	test = getcwd(NULL, 0);
	if (test == NULL)
		ft_putstr_fd("piphell: Error in pwd\n", 2);
	else
	{
		ft_putstr_fd(test, 1);
		write(1, "\n", 1);
	}
	return (0);
}
