/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:46 by abasante          #+#    #+#             */
/*   Updated: 2023/09/27 13:41:40 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../expand/expand.h"

int	before_execution(t_cmnd *node, t_env *env)
{
	t_cmnd	*tmp;
	int		i;

	i = 0;
	tmp = node;
	while (tmp != NULL)
	{
		tmp->cmd_pth = find_path(&tmp, env);
		node->built_ptr = check_if_builtin(&tmp);
		if (!node->cmd)
			i++;
		else if (tmp->cmd_pth == NULL && node->built_ptr != &export \
			&& node->built_ptr != &exit_builtin && node->built_ptr != &unset)
		{
			i++;
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(tmp->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit_status("set", 127);
		}
		tmp = tmp->next;
	}
	return (i);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	execute(t_cmnd	*node, t_env *env, char **envp)
{
	if (node->redirs.o_r_type != 3 && node->redirs.o_r_type != 0)
	{
		dup2(node->redirs.o_fd, STDOUT_FILENO);
		close(node->redirs.o_fd);
	}
	else if (node->redirs.o_r_type == 3 || node->redirs.i_r_type == 3)
	{
		if (node->redirs.o_r_type == 3)
			dup2(node->redirs.out_pipe[1], STDOUT_FILENO);
		else
			dup2(node->redirs.in_pipe[0], STDIN_FILENO);
		close_pipe(node->redirs.out_pipe);
		if (node->prev->redirs.o_r_type == 3)
			close_pipe(node->prev->redirs.out_pipe);
	}
	if (node->redirs.i_fd != STDIN_FILENO)
	{
		dup2(node->redirs.i_fd, STDIN_FILENO);
		close(node->redirs.i_fd);
	}
	if (node->built_ptr != NULL)
		exit(node->built_ptr(env, node->cmd));
	else
		execve(node->cmd_pth, node->cmd, envp);
}

void	make_pipe(t_cmnd **node)
{
	int	fd[2];

	pipe(fd);
	if ((*node)->redirs.i_r_type == 3)
	{
		(*node)->redirs.in_pipe = malloc(2 * sizeof(int));
		(*node)->redirs.in_pipe[0] = dup(fd[0]);
		(*node)->redirs.in_pipe[1] = dup(fd[1]);
	}
	if ((*node)->prev->redirs.o_r_type == 3)
	{
		(*node)->prev->redirs.out_pipe = malloc(2 * sizeof(int));
		(*node)->prev->redirs.out_pipe[0] = dup(fd[0]);
		(*node)->prev->redirs.out_pipe[1] = dup(fd[1]);
	}
	close(fd[0]);
	close(fd[1]);
}

void	fork_loop(t_cmnd **node, t_env *env, char **envp)
{
	t_cmnd				*tmp;
	int					pid2;

	tmp = *node;
	if (tmp->prev != NULL)
	{
		if (tmp->prev->redirs.o_r_type == 3 || tmp->redirs.i_r_type == 3)
			make_pipe(&tmp);
		pid2 = fork();
		if (pid2 == 0)
			fork_loop(&(*node)->prev, env, envp);
		waitpid(pid2, NULL, 0);
	}
	execute(tmp, env, envp);
}
