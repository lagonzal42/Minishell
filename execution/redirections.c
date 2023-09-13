#include "execution.h"

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
		if (tmp->cmd_pth == NULL)
		{
			i++;
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(tmp->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		}
		node->built_ptr = check_if_builtin(&tmp); 
		tmp = tmp->next;
	}
	return (i);
}

void	execute(t_cmnd	*node, t_env *env)
{
	printf("%d\n", node->redirs.i_fd);
	if (node->redirs.o_r_type != 0)
        dup2(node->redirs.o_fd, STDOUT_FILENO);
    if (node->redirs.i_r_type != 0)
        dup2(node->redirs.i_fd, STDIN_FILENO);
	if (node->built_ptr != NULL)
		node->built_ptr(env, node->cmd);
	else
		execve(node->cmd_pth, node->cmd, NULL);
}

void	fork_loop(t_cmnd *node, t_env *env)
{
	t_cmnd	*tmp;
	int	pid;

	tmp = node;
	while (tmp != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			execute(tmp, env);
		}
		wait(NULL);
		tmp = tmp->next;
		//printf("aaaaaaa\n");
	}
	wait(NULL);
	printf("bbbbbbb\n");
	exit (0);
}

int	main(int ac, char **av, char **envp)
{
	char	**str;
	t_cmnd	*cmds;
	t_env	*env;
	ac = 0;
	av = NULL;
	cmds = NULL;
	env = NULL;

	cmds = cmnd_init();
	str = malloc(5 * sizeof(char *));
	str[4] = NULL;
	str[0] = ft_strdup("pwd");
    str[1] = ft_strdup("");
	str[2] = ft_strdup("|");
	str[3] = ft_strdup("cat>infile");
	//str[4] = ft_strdup("pwd");
	env = get_env(envp, env);
	if (node_create(str, &cmds))
	 	ft_printf("FAILED WHILE OPENING FDS\n");
	if (before_execution(cmds, env) != 0)
		return (1);
	print_commands(cmds);
	fork_loop(cmds, env);	
	free_cmnds(cmds);
	ft_double_free(str);
}
