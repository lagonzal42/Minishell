/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:14:40 by abasante          #+#    #+#             */
/*   Updated: 2023/09/27 13:15:30 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*get_env(char **envp, t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	env = make_node();
	tmp = env;
	while (envp[i] != NULL)
	{
		tmp->name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		tmp->value = ft_substr(envp[i], ft_strchr(envp[i], '=') - envp[i] + 1,
				ft_strlen(envp[i]));
		if (envp[++i])
		{
			ft_lstadd_back(env, tmp);
			tmp->next = make_node();
			tmp = tmp->next;
		}
	}
	return (env);
}
