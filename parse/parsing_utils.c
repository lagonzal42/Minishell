/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:19:35 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/18 13:40:44 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse.h"
# include <stdio.h>

t_cmnd	*cmnd_init(void)
{
	t_cmnd	*new;

	new = malloc(sizeof(t_cmnd));
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
void	add_back(t_cmnd *lst, t_cmnd *new)
{
	t_cmnd *nav;

	if (!lst)
		lst = new;
	else
	{
		nav = lst;
		while (nav->next)
			nav = nav->next;
		nav->next = new;
	}
}
int	find_quoute_end(char *trimed)
{
	int	n;

	n = 1;
	printf("simple quoute detected\n");
	while (trimed[n] && trimed[n] != '\'')
		n++;
	return (n);
}

int	find_d_quoute_end(char *trimed)
{
	int	n;

	n = 1;
	printf("double quoute detected\n");
	while (trimed[n] && trimed[n] != '\"')
	{
		n++;
		if (trimed[n] == '\"' && trimed[n - 1] == 92)
			n++;
	}
	return (n);
}