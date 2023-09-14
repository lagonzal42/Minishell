#include "execution.h"
#include "../expand/expand.h"

/*I am going to receive the t_cmnd structure:
    1:char **cmd, which are going to be the commands already splited.
    2:int   prev_pid, not sure what i am going to use this for yet, but it is the previous process id
    3:struct s_cmnd *next and struct s_cmnd *prev, each node is almost as if it was the command line separated with pipes.
    4:struct s_redir redirs-> this will be used to know the type of redirection*/

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
	if (tmp->prev != NULL)
	{
		printf("enters\n");
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

// int	main(int ac, char **av, char **envp)
// {
// 	char	**str;
// 	t_cmnd	*cmds;
// 	t_env	*env;
// 	ac = 0;
// 	av = NULL;
// 	cmds = NULL;
// 	env = NULL;

// 	cmds = cmnd_init();
// 	str = malloc(5 * sizeof(char *));
// 	str[4] = NULL;
// 	str[0] = ft_strdup("pwd");
//     str[1] = ft_strdup("");
// 	str[2] = ft_strdup("|");
// 	str[3] = ft_strdup("cat>infile");
// 	//str[4] = ft_strdup("pwd");
// 	env = get_env(envp, env);
// 	if (node_create(str, &cmds))
// 	 	ft_printf("FAILED WHILE OPENING FDS\n");
// 	if (before_execution(cmds, env) != 0)
// 		return (1);
// 	print_commands(cmds);
// 	fork_loop(cmds, env);	
// 	free_cmnds(cmds);
// 	ft_double_free(str);
// }
