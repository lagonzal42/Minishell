/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:16:12 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/11 13:46:34 by lagonzal         ###   ########.fr       */
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
	while (spltd[n] && !e)
	{
		m = 0;
		while (spltd[n][m])
		{
			ft_printf("m: %d\n", m);
			if (spltd[n][m] == '<' || spltd[n][m] == '>' || spltd[n][m] == '|')
				e = select_redirection(spltd, &n, &m, &tmp);
			else
			{
				e = add_cmnd(spltd[n], &m, &tmp);
			}
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
		if ((*tmp)->redirs.i_r_type)
			close((*tmp)->redirs.o_fd);
		return (get_o_redir(get_next_word(spltd, n, m, tmp), tmp));
	}
	else
		return (pipe_case(tmp));	
}

static char	*get_next_word(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	char	*holder;

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
	holder = ft_substr(&spltd[*n][*m], 0, find_next_meta(&spltd[*n][*m]));
	return (*m += ft_strlen(holder) - 1, q_t(holder));
}

int	main(void)
{
	char	**str;
	t_cmnd	*cmds;

	cmds = NULL;
	cmds = cmnd_init();
	str = malloc(6 * sizeof(char *));
	str[5] = NULL;
	str[0] = ft_strdup("echo>outfile1");
	str[1] = ft_strdup("hello");
	str[2] = ft_strdup("|");
	str[3] = ft_strdup("cat<inf\"ile\"1");
	str[4] = ft_strdup(">>outfile2");
	if (node_create(str, &cmds))
		ft_printf("FAILED WHILE OPENING FDS\n");
	else
		print_commands(cmds);
	free_cmnds(cmds);
	ft_double_free(str);
}
