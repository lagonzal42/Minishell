#include "execution.h"

/*I am going to receive the t_cmnd structure:
    1:char **cmd, which are going to be the commands already splited.
    2:int   prev_pid, not sure what i am going to use this for yet, but it is the previous process id
    3:struct s_cmnd *next and struct s_cmnd *prev, each node is almost as if it was the command line separated with pipes.
    4:struct s_redir redirs-> this will be used to know the type of redirection*/

void    execute(t_cmnd  *node, t_env *env)
{
    // if (node->redirs.o_r_type != 0)
    //     dup2(node->redirs.o_fd, STDOUT_FILENO);
    // if (node->redirs.i_r_type != 0)
    //     dup2(node->redirs.i_fd, STDIN_FILENO);
	t_cmnd	*tmp;
	int n =0;

	tmp = node;
	ft_putstr_fd("AAAAAAAA\n", STDOUT_FILENO);	
	while (tmp != NULL)
	{
		printf("%d\n", n++);
		tmp->cmd_pth = find_path(&tmp, env);
		if (tmp->cmd_pth == NULL)
		{
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(tmp->cmd[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);

		}
		printf("path:%s\n", tmp->cmd_pth);
		tmp = tmp->next;
	}
}

void	execute_builtins(t_cmnd	*node, t_env *env)
{
	char	*string_in_node;

	string_in_node = ft_strdup(node->cmd[0]);
	if (ft_strcmp(string_in_node, "echo") == 0)
		echo(env, node->cmd);
	else if (ft_strcmp(string_in_node, "cd") == 0)
		cd(env, node->cmd);
	else if (ft_strcmp(string_in_node, "env") == 0)
		print_env(env, NULL);
	// else if (ft_strcmp(string_in_node, "exit") == 0)
	// 	exit_builtin();
	else if (ft_strcmp(string_in_node, "export") == 0)
		export(env, node->cmd);
	else if (ft_strcmp(string_in_node, "pwd") == 0)
		pwd(env, node->cmd);
	else if (ft_strcmp(string_in_node, "unset") == 0)
		unset(env, node->cmd);
	free(string_in_node);
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
	str = malloc(6 * sizeof(char *));
	str[5] = NULL;
	str[0] = ft_strdup("aksdfasdf>outfile1");
    str[1] = ft_strdup("hello good morning");
	str[2] = ft_strdup("|");
	str[3] = ft_strdup("cat>nf\"ile\"1");
	str[4] = ft_strdup("pwd");
	env = get_env(envp, env);
	printf("AAAAAAAAAAAAAAAAA\n");
	if (node_create(str, &cmds))
	 	ft_printf("FAILED WHILE OPENING FDS\n");
    // bon = check_if_builtin(&cmds);
	// printf("built in or not:%d if it is 1 if it's not 0\n", bon);
	// if (bon == 1)
	// 	execute_builtins(cmds, env);
	// path = find_path(&cmds, env);

	execute(cmds, env);
	free_cmnds(cmds);
	ft_double_free(str);
}
