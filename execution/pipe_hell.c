/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_hell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:46 by abasante          #+#    #+#             */
/*   Updated: 2023/11/06 20:21:12 by lagonzal         ###   ########.fr       */
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
		if (!tmp->cmd)
		{
			i++;
			ft_putstr_fd("Error, command not found\n", 2);
		}
		else if (tmp->cmd_pth == NULL && node->built_ptr != &export \
			&& node->built_ptr != &exit_builtin && node->built_ptr != &unset)
		{
			i++;
			ft_putstr_fd(tmp->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit_status("set", 127);
		}
		tmp = tmp->next;
	}
	return (i);
}

void	close_pipes(int **pipes)
{
	//ft_putstr_fd("close pipes\n", 2);
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
}

void	close_redirs(t_cmnd *node)
{
	if (node->redirs.o_r_type != 3 && node->redirs.o_r_type != 0)
		close(node->redirs.o_fd);
	if (node->redirs.i_r_type != 3 && node->redirs.i_r_type != 0)
		close(node->redirs.i_fd);
}

void	execution(t_cmnd *node, t_env *env, char **envp, int **pipes)
{
	if (node->redirs.i_r_type == 3)
		dup2(pipes[0][0], STDIN_FILENO);
	if (node->redirs.o_r_type == 3)
		dup2(pipes[1][1], STDOUT_FILENO);
	if (node->redirs.o_r_type && node->redirs.i_r_type != 3)
		dup2(node->redirs.o_fd, STDOUT_FILENO);
	if (node->redirs.i_r_type && node->redirs.i_r_type != 3)
		dup2(node->redirs.i_fd, STDIN_FILENO);
	close_pipes(pipes);
	close_redirs(node);
	if (node->built_ptr != NULL && node->built_ptr != &exit_builtin)
		exit(node->built_ptr(env, node->cmd));
	else
		execve(node->cmd_pth, node->cmd, envp);
}

void	call_the_piper(int *in_pipe, int *out_pipe)
{
	close(in_pipe[0]);
	close(in_pipe[1]);
	in_pipe[0] = dup(out_pipe[0]);
	in_pipe[1] = dup(out_pipe[1]);
	close(out_pipe[0]);
	close(out_pipe[1]);
}

void	fork_loop(t_cmnd **node, t_env *env, char **envp)
{
	t_cmnd				*tmp;
	int					in_pipe[2];
	int					out_pipe[2];
	int					**pipes;
	int					pid;

	tmp = *node;
	pipes = malloc(sizeof(int *) * 2);
	pipe(in_pipe);
	if (tmp->next != NULL)
	{
		pipe(out_pipe);
		pipes[0] = in_pipe;
		pipes[1] = out_pipe;
		pid = fork();
		if (pid == 0)
			execution(tmp, env, envp, pipes);
		else
			waitpid(pid, NULL, 0);
		call_the_piper(in_pipe, out_pipe);
		tmp = tmp->next;
	}
	execution(tmp, env, envp, pipes);
}
