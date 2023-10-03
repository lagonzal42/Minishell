/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:58:35 by abasante          #+#    #+#             */
/*   Updated: 2023/10/03 15:19:26 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	go_back(t_env *env)
{
	char	cwd[10000];
	char	cwd1[10000];

	getcwd(cwd, sizeof(cwd));
	if (chdir("..") == 0)
	{
		getcwd(cwd1, sizeof(cwd1));
		update_oldpwd(env, ft_strdup(cwd));
		update_pwd(env, ft_strdup(cwd1));
		return (SUCCESS);
	}
	else
	{
		if (access("..", F_OK) == -1)
			ft_putstr_fd("No such file or directory: ", 1);
		else if (access("..", R_OK) == -1)
			ft_putstr_fd("permission denied: ", 1);
		ft_putstr_fd("Chdir failed in go_back\n", 1);
		return (ERROR);
	}
}

int	do_whatever(void)
{
	if (chdir(".") == 0)
		return (SUCCESS);
	else
	{
		if (access(".", F_OK) == -1)
			ft_putstr_fd("No such file or directory: ", 1);
		else if (access("..", R_OK) == -1)
			ft_putstr_fd("permission denied: ", 1);
		ft_putstr_fd("Chdir failed in do_whatever\n", 1);
		return (ERROR);
	}
}

int	cd(t_env *env, char **args)
{
	int	i;

	i = 0;
	if (!args[1] || args[1][0] == '~')
		i = home_case(env);	
	else if (args[1][0] == '/' && args[1][1] == '\0')
		i = slash_case(env);
	else if (args[1][0] == '.' && args[1][1] == '.')
		i = go_back(env);
	else if (args[1][0] == '.')
		i = do_whatever();	
	else if (args[1])
		i = absolute_path(env, args[1]);
	return (i);
}
