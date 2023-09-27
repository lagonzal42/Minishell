/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:10:53 by abasante          #+#    #+#             */
/*   Updated: 2023/09/27 13:11:16 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(t_env *env, char **cmd)
{
	char	*test;

	env = 0;
	test = getcwd(NULL, 0);
	if (test == NULL || cmd[1])
		ft_putstr_fd("Error in pwd\n", 1);
	else
	{
		ft_putstr_fd(test, 1);
		write(1, "\n", 1);
	}
	return (0);
}
