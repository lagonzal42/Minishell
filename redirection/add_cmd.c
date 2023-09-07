/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larra <larra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:59:11 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/07 10:52:54 by larra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../expand/expand.h"

int	add_cmnd(char *spltd, int *m, t_cmnd **tmp)
{
	char	*holder;
	int		end;

	ft_printf("cmnd adding case\n");
	end = find_next_meta(&spltd[*m]);
	ft_printf("string on right  is: %s\n", &spltd[end]);
	holder = ft_substr(&spltd[*m], 0, end);
	ft_printf("cmnd to add is: %s\n", holder); //debug
	if (!holder)
		return (1);
	*m += ft_strlen(holder) - 1;
	ft_printf("===========ADD CMD=================\n"); //debug
	(*tmp)->cmd = ft_resize((*tmp)->cmd, holder);
	ft_double_print(((*tmp)->cmd));
	ft_printf("===========ADD CMD END=============\n"); //debug
	if (!(*tmp)->cmd)
		return (1);
	return (0);
}
