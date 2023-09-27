/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:35:21 by abasante          #+#    #+#             */
/*   Updated: 2023/09/27 13:36:10 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*find_path(t_cmnd **node, t_env *env)
{
	int		i;
	int		j;
	int		a;
	char	**bin_paths;
	char	*holder;

	i = 0;
	j = 0;
	a = 1;
	if (!(*node)->cmd)
		return (0);
	if (access((*node)->cmd[0], F_OK | X_OK) != -1)
		return (ft_strdup((*node)->cmd[0]));
	while (env && env->name && ft_strncmp(env->name, "PATH", 4) != 0)
		env = env->next;
	bin_paths = ft_split(env->value, ':');
	holder = loop(bin_paths, node);
	ft_double_free(bin_paths);
	if (holder != NULL)
		return (holder);
	else
		return (NULL);
}

char	*loop(char **bin_paths, t_cmnd **node)
{
	int		j;
	int		a;
	char	*holder;
	char	*moment;

	a = 1;
	j = 0;
	while (bin_paths[j] && a == 1)
	{
		moment = ft_strjoin(bin_paths[j], "/");
		holder = ft_strjoin(moment, (*node)->cmd[0]);
		j++;
		a = check_if_access(holder);
		if (a == 1)
		{
			free(holder);
			free(moment);
			holder = NULL;
			moment = NULL;
		}
	}
	return (free(moment), holder);
}
