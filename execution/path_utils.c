/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:24 by abasante          #+#    #+#             */
/*   Updated: 2023/09/27 13:36:34 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_if_path_absolute(char *cmd)
{
	if (cmd[0] == '/')
		return (0);
	else
		return (1);
}

int	execute_commands_path(char *path_name, char **av, char **envp)
{
	if (execve(path_name, av, envp) == -1)
		return (0);
	return (0);
}

int	check_if_access(char *holder)
{
	if (access(holder, F_OK | X_OK) == -1)
		return (1);
	return (0);
}
