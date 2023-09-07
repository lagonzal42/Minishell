#include "execution.h"

/*I am going to receive the t_cmnd structure:
    1:char **cmd, which are going to be the commands already splited.
    2:int   prev_pid, not sure what i am going to use this for yet, but it is the previous process id
    3:struct s_cmnd *next and struct s_cmnd *prev, each node is almost as if it was the command line separated with pipes.
    4:struct s_redir redirs-> this will be used to know the type of redirection*/


/*First I am going to consider the following case: echo "hello" > file.txt
  in this case i am going to be redirecting the output of the echo hello command into the file.txt
  */
void    execute(char **cmd)
{
    int l;
    int s;
    int type;

    l = 0;
    s = 0;
//while (node->next != NULL);
    type = check_type(node);
}

int main(void)
{
  char **cmd;

  cmd = malloc(4 * sizeof(char *));
  cmd[0] = ft_strdup("echo");
  cmd[1] = ft_strdup("hello");
  cmd[2] = ft_strdup(">");
  cmd[3] = ft_strdup("hello.txt");
  execute(cmd);
}
