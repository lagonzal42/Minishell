/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:02:53 by abasante          #+#    #+#             */
/*   Updated: 2023/09/27 13:03:22 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	update_oldpwd(t_env *env, char *oldpwd)
{
	t_env	*tmp;
	char	*name;

	name = "OLDPWD";
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			tmp->value = oldpwd;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	home_case(t_env *env)
{
	char	*home_path;
	char	*home;
	char	cwd[10000];

	home = "HOME";
	home_path = search_for_var(env, home);
	getcwd(cwd, sizeof(cwd));
	if (chdir(home_path) == 0)
	{
		update_oldpwd(env, cwd);
		return (SUCCESS);
	}
	else
	{
		ft_putstr_fd("cd: HOME not set", 1);
		ft_putstr_fd("Chdir failed in home_case\n", 1);
		return (ERROR);
	}
}

int	slash_case(t_env *env)
{
	char	cwd[10000];

	getcwd(cwd, sizeof(cwd));
	if (chdir("/") == 0)
	{
		update_oldpwd(env, cwd);
		return (SUCCESS);
	}
	else
	{
		if (access("/", F_OK) == -1)
			ft_putstr_fd("no such file or directory: ", 1);
		else if (access("/", R_OK) == -1)
			ft_putstr_fd("permission denied: ", 1);
		ft_putstr_fd("Chdir failed in slash_case\n", 1);
		return (ERROR);
	}
}

int	absolute_path(t_env *env, char *absolute_path)
{
	char	cwd[10000];

	getcwd(cwd, sizeof(cwd));
	if (chdir(absolute_path) == 0)
	{
		update_oldpwd(env, cwd);
		return (SUCCESS);
	}
	else
	{
		if (access(absolute_path, F_OK) == -1)
			ft_putstr_fd("No such file or directory: ", 1);
		else if (access(absolute_path, R_OK) == -1)
			ft_putstr_fd("permission denied: ", 1);
		ft_putstr_fd("Chdir failed in absolute_path\n", 1);
		return (ERROR);
	}
}
