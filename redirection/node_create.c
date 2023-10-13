/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:16:12 by lagonzal          #+#    #+#             */
/*   Updated: 2023/10/13 16:29:45 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../expand/expand.h"

static int	select_redirection(char **spltd, int *n, int *m, t_cmnd **tmp);
static char	*get_next_word(char **spltd, int *n, int *m, t_cmnd **tmp);

int	node_create(char **spltd, t_cmnd **head)
{
	int		n;
	int		m;
	int		e;
	t_cmnd	*tmp;

	n = 0;
	e = 0;
	tmp = *head;
	while (!e && spltd[n])
	{
		m = 0;
		while (!e && spltd[n][m])
		{
			if (spltd[n][m] == '<' || spltd[n][m] == '>' || spltd[n][m] == '|')
				e = select_redirection(spltd, &n, &m, &tmp);
			else
				e = add_cmnd(spltd[n], &m, &tmp);
			m++;
		}
		n++;
	}
	return (e);
}

static int	select_redirection(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	if (spltd[*n][*m] == '<')
	{
		if ((*tmp)->redirs.i_r_type)
			close_previous_in(tmp);
		return (get_i_redir(get_next_word(spltd, n, m, tmp), tmp));
	}
	else if (spltd[*n][*m] == '>')
	{
		if ((*tmp)->redirs.o_r_type && (*tmp)->redirs.o_fd != 1)
			close((*tmp)->redirs.o_fd);
		return (get_o_redir(get_next_word(spltd, n, m, tmp), tmp));
	}
	else
		return (pipe_case(tmp));
}

static void	advance(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	if (spltd[*n][*m] == spltd[*n][*m + 1])
	{
		if (spltd[*n][*m] == '>')
			(*tmp)->redirs.o_r_type = 2;
		else
			(*tmp)->redirs.i_r_type = 2;
		*m += 2;
	}
	else
	{
		if (spltd[*n][*m] == '>')
			(*tmp)->redirs.o_r_type = 1;
		else
			(*tmp)->redirs.i_r_type = 1;
		*m += 1;
	}
	if (spltd[*n][*m] == '\0')
	{
		*n += 1;
		*m = 0;
	}
}

static char	*get_next_word(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	char	*holder;
	int		o_n;
	int		o_m;

	o_n = *n;
	o_m = *m;
	advance(spltd, n, m, tmp);
	holder = ft_substr(&spltd[*n][*m], 0, find_next_meta(&spltd[*n][*m]));
	if (ft_strlen(holder) != 0)
		return (*m += ft_strlen(holder) - 1, q_t(holder));
	else
		return (redir_error(spltd[o_n][o_m]), exit_status("set", 258),
				free(holder), NULL);
}
