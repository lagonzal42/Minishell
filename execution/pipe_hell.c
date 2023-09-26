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

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	execute(t_cmnd	*node, t_env *env, char **envp)
{
	if (node->redirs.o_r_type != 3 && node->redirs.o_r_type != 0)
	{
        dup2(node->redirs.o_fd, STDOUT_FILENO);
		close(node->redirs.o_fd);
	}
	else if (node->redirs.o_r_type == 3)
	{
		dup2(node->redirs.out_pipe[1], STDOUT_FILENO);	
		close_pipe(node->redirs.out_pipe);
	}
    if (node->redirs.i_fd != STDIN_FILENO)
	{
        dup2(node->redirs.i_fd, STDIN_FILENO);
		close(node->redirs.i_fd);
	}
	else if (node->redirs.i_r_type == 3)
	{
		dup2(node->redirs.in_pipe[0], STDIN_FILENO);
		close_pipe(node->redirs.in_pipe);
		if (node->prev->redirs.o_r_type == 3)
			close_pipe(node->prev->redirs.out_pipe);
	}
	if (node->built_ptr != NULL)
		exit(node->built_ptr(env, node->cmd));
	else
		execve(node->cmd_pth, node->cmd, envp);
}

void	make_pipe(t_cmnd **node)
{
	int	fd[2];

	pipe(fd);
	if ((*node)->redirs.i_r_type == 3)
	{
		(*node)->redirs.in_pipe = malloc(2 * sizeof(int));
		(*node)->redirs.in_pipe[0] = dup(fd[0]);
		(*node)->redirs.in_pipe[1] = dup(fd[1]);
	}
	if ((*node)->prev->redirs.o_r_type == 3)
	{
		(*node)->prev->redirs.out_pipe = malloc(2 * sizeof(int));
		(*node)->prev->redirs.out_pipe[0] = dup(fd[0]);
		(*node)->prev->redirs.out_pipe[1] = dup(fd[1]);
	}
	close(fd[0]);
	close(fd[1]);
}

void	fork_loop(t_cmnd **node, t_env *env, char **envp)
{
	t_cmnd				*tmp;
	int					pid2;

	tmp = *node;
	if (tmp->prev != NULL)
	{
		if (tmp->prev->redirs.o_r_type == 3 || tmp->redirs.i_r_type == 3)
			make_pipe(&tmp);	
		pid2 = fork();
		if (pid2 == 0)
			fork_loop(&(*node)->prev, env, envp);	
		waitpid(pid2, NULL, 0);
	}
	execute(tmp, env, envp);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <sys/wait.h>
// #include <unistd.h>
// int main() {
//     struct sigaction sa;
//     sa.sa_handler = &child_handler;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
//     if (sigaction(SIGCHLD, &sa, 0) == -1) 
// 	{
//         perror(0);
//         exit(1);
//     }
//     pid_t pid = fork();
//     if (pid == 0) 
// 	{  // Child process
//         printf("Child process started, will sleep for 3 seconds...\n");
//         sleep(3);
//         printf("Child process exiting...\n");
//         exit(0);
//     } 
// 	else if (pid > 0) 
// 	{  // Parent process
//         printf("Parent process will sleep for a longer duration...\n");
//         sleep(10);
//         printf("Parent process exiting...\n");
//     } 
// 	else 
// 	{
//         perror("fork");
//         exit(1);
//     }
//     return 0;
// }
