#include "execution.h"

/*I am going to receive the t_cmnd structure:
    1:char **cmd, which are going to be the commands already splited. 
    2:int   prev_pid, not sure what i am going to use this for yet, but it is the previous process id
    3:struct s_cmnd *next and struct s_cmnd *prev, each node is almost as if it was the command line separated with pipes.
    4:struct s_redir redirs-> this will be used to know the type of redirection*/

int main()
{
    int outputFile = open("output.txt", O_WRONLY);

    if (outputFile == -1) 
	{
        perror("Error opening file");
        return 1;
    }

    // Redirect stdout to the file
    int saved_stdout = dup(STDOUT_FILENO);
    dup2(outputFile, STDOUT_FILENO);
    close(outputFile);

    printf("This text will be redirected to output.txt\n");

    // Restore stdout
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    printf("This text will be printed to the console.\n");

    return 0;
}
