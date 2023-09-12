#include "execution.h"

/*I am going to receive the t_cmnd structure:
    1:char **cmd, which are going to be the commands already splited.
    2:int   prev_pid, not sure what i am going to use this for yet, but it is the previous process id
    3:struct s_cmnd *next and struct s_cmnd *prev, each node is almost as if it was the command line separated with pipes.
    4:struct s_redir redirs-> this will be used to know the type of redirection*/

void    execute(t_cmnd  *node)
{
    if (node->redirs.o_r_type != 0)
        dup2(node->redirs.o_fd, STDOUT_FILENO);
    if (node->redirs.i_r_type != 0)
        dup2(node->redirs.i_fd, STDIN_FILENO);
	// if (check_if_path_absolute((*node)->cmd[0]) == 0)
	// 	execve();
	
}

void	execute_builtins(t_cmnd	*node, t_env *env)
{
	
}

int	main(int ac, char **av, char **envp)
{
	char	**str;
	char 	*path;
	t_cmnd	*cmds;
	t_env	*env;
	int		bon;

	env = get_env(envp, env);
	cmds = NULL;
	cmds = cmnd_init();
	str = malloc(3 * sizeof(char *));
	str[2] = NULL;
	str[0] = ft_strdup("echo>outfile1");
    str[1] = ft_strdup("hello good morning");
	// str[1] = ft_strdup("|");
	// str[2] = ft_strdup("cat<<inf\"ile\"1");
	// str[3] = ft_strdup(">>outfile2");
	if (node_create(str, &cmds))
	 	ft_printf("FAILED WHILE OPENING FDS\n");
    bon = check_if_builtin(&cmds);
	printf("built in or not:%d if it is 1 if it's not 0\n", bon);
	path = find_path(bon, &cmds, env);
	execute(cmds);
	free_cmnds(cmds);
	ft_double_free(str);
}
