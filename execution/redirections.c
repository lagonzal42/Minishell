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
		printf("%s\n", tmp->cmd_pth);
		node->built_ptr = check_if_builtin(&tmp);
		if (tmp->cmd_pth == NULL && node->built_ptr != &export\
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

void	execute(t_cmnd	*node, t_env *env)
{
	if (node->redirs.o_r_type != 0)
        dup2(node->redirs.o_fd, STDOUT_FILENO);
    if (node->redirs.i_r_type != 0)
        dup2(node->redirs.i_fd, STDIN_FILENO);
	if (node->redirs.i_r_type == 3 && node->prev && node->prev->redirs.o_r_type == 3)
		waitpid(node->prev->pid, NULL, 0);
	if (node->built_ptr != NULL)
		node->built_ptr(env, node->cmd);
	else
		execve(node->cmd_pth, node->cmd, NULL);
}

void	fork_loop(t_cmnd **node, t_env *env)
{
	t_cmnd	*tmp;
	int	pid2;
	static int	i;
	
	tmp = *node;
	printf("%p\n", (*node)->prev);
	printf("execution: %d\n", i++);
	printf("execution: %d\n", i);
	if (tmp->prev != NULL)
	{
		printf("ENTERS\n");
		pid2 = fork();
		if (pid2 != 0)
		{
			printf("enters2\n");
			fork_loop(&(*node)->prev, env);
		}
		else if ((*node)->redirs.i_r_type == 3 && (*node)->prev->redirs.o_r_type == 3)
			waitpid(-1, NULL, 0);
	}
	execute(tmp, env);
}
