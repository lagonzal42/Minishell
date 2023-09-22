#include "execution.h"
#include "../expand/expand.h"

int    before_execution(t_cmnd  *node, t_env *env)
{
	t_cmnd	*tmp;
	int i;

	i = 0;
	tmp = node;
	while (tmp != NULL)
	{
		tmp->cmd_pth = find_path(&tmp, env);
		node->built_ptr = check_if_builtin(&tmp);
		if (!node->cmd)
			i++;
		else if (tmp->cmd_pth == NULL && node->built_ptr != &export\
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

void	execute(t_cmnd	*node, t_env *env, char **envp)
{
	if (node->redirs.o_r_type != 0)
	{
        dup2(node->redirs.o_fd, STDOUT_FILENO);
		close(node->redirs.o_fd);
	}
    if (node->redirs.i_r_type != 0)
	{
        dup2(node->redirs.i_fd, STDIN_FILENO);
		close(node->redirs.i_fd);
	}
	if (node->built_ptr != NULL)
		exit(node->built_ptr(env, node->cmd));
	else
		execve(node->cmd_pth, node->cmd, envp);
}

void	fork_loop(t_cmnd **node, t_env *env, char **envp)
{
	t_cmnd	*tmp;
	int	pid2;

	tmp = *node;
	if (tmp->prev != NULL)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			//pregunta por que aqui queremos que entre el proceso padre al if
			fork_loop(&(*node)->prev, env, envp);
		}
		if ((*node)->redirs.i_r_type == 3 && (*node)->prev->redirs.o_r_type == 3)
			wait(NULL);
	}
	execute(tmp, env, envp);
}
