/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:59:46 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/06 19:02:08 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <stddef.h>

t_cmnd	*cmnd_init(void)
{
	t_cmnd	*new;

	new = malloc(sizeof(t_cmnd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->redirs.i_r_type = 0;
	new->redirs.o_r_type = 0;
	new->redirs.i_fd = 0;
	new->redirs.o_fd = 1;
	new->redirs.h_lim = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	redir_error(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
}

void	close_previous_in(t_cmnd **tmp)
{
	if ((*tmp)->redirs.i_r_type == 1 || (*tmp)->redirs.i_r_type == 3)
	{
		close((*tmp)->redirs.i_fd);
		(*tmp)->redirs.i_fd = 0;
	}
	else if ((*tmp)->redirs.i_r_type == 3)
	{
		free((*tmp)->redirs.h_lim);
		(*tmp)->redirs.h_lim = NULL;
	}
}

int	find_next_meta(char *spltd)
{
	int	n;
	int	quouted;

	n = 0;
	quouted = 0;
	while (spltd[n] && ((spltd[n] != '<' && spltd[n] != '>' && spltd[n] != '|') || quouted))
	{
		if (spltd[n] == '\"' && (quouted == 1 || !quouted))
		{
			if (quouted)
				quouted = 0;
			else
				quouted = 1;
		}
		else if (spltd[n] == '\'' && (quouted == 2 || !quouted))
		{
			if (quouted)
				quouted = 0;
			else 
				quouted = 2;
		}
		n++;
	}
	return (n);
}
