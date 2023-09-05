/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:45:08 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/05 21:02:51 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <fcntl.h>

int	get_i_redir(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	char *holder;

	if (spltd[*n][*m] == spltd[*n][*m + 1])
		return (get_heredoc_redir(spltd, n, m, tmp));
	else
	{
		ft_printf("input simple redir case %s\n", &spltd[*n][*m]);
		*m += 1;
		if (spltd[*n][*m] == '\0')
		{
			*n += 1;
			*m = 0; 
		}
		holder = ft_substr(&spltd[*n][*m], 0, find_next_meta(&spltd[*n][*m]));
		if (ft_strlen(holder) == 0)
			return (redir_error(spltd[*n][*m]), free(holder), 1);
		(*tmp)->redirs.i_fd = open(holder, O_RDONLY);
		if ((*tmp)->redirs.i_fd == -1)
			return (1);
		printf("fd name is: %s\n", holder);  //this needs dup?.
		return (*m += ft_strlen(holder) - 1, free(holder), 0);
	}
}

int	get_heredoc_redir(char **spltd, int *n, int *m,t_cmnd *tmp)
{
	
}