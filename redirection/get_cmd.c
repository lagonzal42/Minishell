/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:59:11 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/05 16:18:02 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../expand/expand.h"

int	find_next_meta(char *spltd);

int	add_cmd(char *spltd, int *m, t_cmnd **tmp)
{
	char	*holder;
	int		end;

	end = find_next_meta(&spltd[*m]);
	holder = ft_substr(&spltd[*m], 0, end);
	if (!holder)
		return (1);
	ft_printf("cmnd to add is: %s\n", holder);
	ft_resize((*tmp)->cmd, holder);
	if (!(*tmp)->cmd)
		return (1);
	return (0);
}

int	find_next_meta(char *spltd)
{
	int	n;

	n = 0;
	while (spltd[n] && spltd[n] != '<' && spltd[n] != '>' && spltd[n] != '|')
		n++;
	return (n);
}