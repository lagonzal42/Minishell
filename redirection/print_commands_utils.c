/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:34:13 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/27 13:50:20 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"redirection.h"

void	print_commands(t_cmnd *head)
{
	t_cmnd	*tmp;
	int		n;

	n = 0;
	tmp = head;
	while (tmp)
	{
		ft_printf("===========COMAND %d=============\n", n);
		ft_printf("CMD:=============================\n");
		ft_double_print(tmp->cmd);
		ft_printf("=================================\n");
		ft_printf("REDIRS===========================\n");
		ft_printf("input redir type: %d\n", tmp->redirs.i_r_type);
		ft_printf("output redir type %d\n", tmp->redirs.o_r_type);
		if (tmp->redirs.h_lim)
			ft_printf("heredoc limit is %s", tmp->redirs.h_lim);
		tmp = tmp->next;
		n++;
	}
}

void	free_cmnds(t_cmnd *cmds)
{
	t_cmnd	*next;

	next = cmds->next;
	while (next)
	{
		if (cmds->cmd)
			ft_double_free(cmds->cmd);
		if (cmds->redirs.h_lim)
			free(cmds->redirs.h_lim);
		if (cmds->redirs.i_r_type == 3)
			free(cmds->redirs.in_pipe);
		if (cmds->redirs.o_r_type == 3)
			free(cmds->redirs.out_pipe);
		free (cmds);
		cmds = next;
		next = cmds->next;
	}
	if (cmds->cmd)
		ft_double_free(cmds->cmd);
	if (cmds->redirs.h_lim)
		free(cmds->redirs.h_lim);
	if (cmds->redirs.i_r_type == 3)
		free(cmds->redirs.in_pipe);
	if (cmds->redirs.o_r_type == 3)
		free(cmds->redirs.out_pipe);
	free(cmds);
}
