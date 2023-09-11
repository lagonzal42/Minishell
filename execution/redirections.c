#include "execution.h"

/*I am going to receive the t_cmnd structure:
    1:char **cmd, which are going to be the commands already splited.
    2:int   prev_pid, not sure what i am going to use this for yet, but it is the previous process id
    3:struct s_cmnd *next and struct s_cmnd *prev, each node is almost as if it was the command line separated with pipes.
    4:struct s_redir redirs-> this will be used to know the type of redirection*/


/*First I am going to consider the following case: echo "hello" > file.txt
  in this case i am going to be redirecting the output of the echo hello command into the file.txt
  */

void    check_if_builtin(t_cmnd *node)
{
    
}

void    execute(t_cmnd  *node)
{
    printf("===========INSIDE EXECUTE==============\n");
    if (node->redirs.o_r_type != 0)
        dup2(node->redirs.o_fd, STDOUT_FILENO);
    if (node->redirs.i_r_type != 0)
        dup2(node->redirs.i_fd, STDIN_FILENO);
}

int	main(void)
{
	char	**str;
	t_cmnd	*cmds;

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
    check_if_builtin(cmds);
	execute(cmds);
	free_cmnds(cmds);
	ft_double_free(str);
}
