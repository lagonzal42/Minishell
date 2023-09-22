/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:59:11 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/22 15:16:16 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "redirection.h"
#include "../expand/expand.h"

int	add_cmnd(char *spltd, int *m, t_cmnd **tmp)
{
	char	*holder;
	int		end;
	char	*unquouted;

	end = find_next_meta(&spltd[*m]);
	holder = ft_substr(&spltd[*m], 0, end);
	*m += ft_strlen(holder) - 1;
	unquouted = q_t(holder);
	if (!holder)
		return (1);
	(*tmp)->cmd = ft_resize((*tmp)->cmd, unquouted);
	if (!(*tmp)->cmd)
		return (free(unquouted), 1);
	return (0);
}
