/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:16:12 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/06 17:23:28 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../expand/expand.h"


static int	select_redirection(char **spltd, int *n, int *m, t_cmnd **tmp);

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

static int	select_redirection(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	if (spltd[*n][*m] == '<')
		return (get_i_redir(spltd, n, m, tmp));
	else if (spltd[*n][*m] == '>')
		return (get_o_redir(spltd, n, m, tmp));
	else
		return (pipe_case(tmp));	
}

int	main(void)
{
	char	**str;
	t_cmnd	*cmds;
	t_cmnd	*tmp;

	cmds = NULL;
	cmds = cmnd_init();
	str = malloc(5 * sizeof(char *));
	str[4] = NULL;
	str[0] = ft_strdup("echo>>infile");
	str[1] = ft_strdup("|");
	str[2] = ft_strdup("cat<<inf\"ile\"");
	str[3] = ft_strdup(">>outfile");
	tmp = NULL;
	if (cmd_create(str, &cmds))
		ft_printf("FAILED WHILE OPENING FDS\n");
	//else
		//ft_print_cmnds(cmds);
	ft_double_free(str);
}