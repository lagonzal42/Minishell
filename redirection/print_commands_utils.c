/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:34:13 by lagonzal          #+#    #+#             */
/*   Updated: 2023/10/13 16:23:43 by lagonzal         ###   ########.fr       */
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

void	free_pipes(t_cmnd *cmd)
{
	if (cmd->redirs.i_r_type == 3)
		free(cmd->redirs.in_pipe);
	if (cmd->redirs.o_r_type == 3)
		free(cmd->redirs.out_pipe);
	if (cmd->redirs.i_r_type == 3)
		free(cmd->redirs.in_pipe);
	if (cmd->redirs.o_r_type == 3)
		free(cmd->redirs.out_pipe);
}

void	free_cmd(t_cmnd *cmds)
{
	if (cmds->cmd)
	{
		ft_double_free(cmds->cmd);
		if (cmds->redirs.h_lim)
			free(cmds->redirs.h_lim);
		if (cmds->redirs.i_r_type == 3)
			free(cmds->redirs.in_pipe);
		if (cmds->redirs.o_r_type == 3)
			free(cmds->redirs.out_pipe);
		if (cmds->cmd_pth)
			free(cmds->cmd_pth);
		free (cmds);
	}
}

void	free_cmnds(t_cmnd *cmds)
{
	t_cmnd	*next;

	next = cmds->next;
	while (next)
	{
		free_cmd(cmds);
		cmds = next;
		next = cmds->next;
	}
	free_cmd(cmds);
}
