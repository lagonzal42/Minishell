/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:16:12 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/05 20:45:14 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../expand/expand.h"


int	select_redirection(char **spltd, int *n, int *m, t_cmnd **tmp);

int	node_create(char **spltd, t_cmnd **head)
{
	int		n;
	int		m;
	int		e;
	t_cmnd	*tmp;

	n = 0;
	e = 0;
	while (spltd[n] && !e)
	{
		while (spltd[n][m])
		{
			if (spltd[n][m] == '<' || spltd[n][m] == '>' || spltd[n][m] == '|')
				e = select_redirection(spltd, &n, &m, &tmp);
			else
				e = add_cmnd(spltd, &n, &m, &tmp);
			m++;
		}
		n++;
	}
	return (e);
}

int	select_redirection(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	if (spltd[*n][*m] == '<')
		return (get_i_redir(spltd, n, m, tmp));
	else if (spltd[*n][*m] == '>')
		return (get_o_redir(spltd, n, m, tmp));
	else
		return (pipe_case(tmp));	
}