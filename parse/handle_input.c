/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:27:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/15 18:00:04 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../builtins/builtins.h"
#include "../redirection/redirection.h"
#include "../execution/execution.h"

/*This function calls all the other parsing functions in order. 
The input is modified by each one of them.

The first function checks for characters that we dont have to process.
As we dont need to process them we simply avoid them by
throwing an error of invalid character.
This way i think is harder to break our code.

The next two fucntions are splits, but the have some special conditions:
	- The first one splits by the spaces but without taking into 
	account the spaces that are between simple or double quoutes.
	- The second one spltis using the pipes, but instead of 
	making them dissapear puts them in a separated array.

After this 2 the expander is called. The expaders job is to substitute the
enviroment variables names that appear in the prompt for the value of 
each variable.

When the expansion is finished next step will be command creation,
quoute triming and then executing the commands.*/

int	prepare_execution(t_cmnd *head, t_env **env, char **envp);
int	execute_one(t_cmnd *node, t_env **env);

int	input_handle(char *input, t_env **env, char **envp)
{
	char	**args;
	t_cmnd	*head;

	if (check_valid(input))
		return (1);
	args = mini_split(input);
	args = pipe_spliter(args);
	args = expand(args, *env);
	head = cmnd_init();
	if (node_create(args, &head))
		return (free_cmnds(head), 2);
	ft_double_free(args);
	if (before_execution(head, *env) != 0)
		return (free_cmnds(head), 3);
	prepare_execution(head, env, envp);
	free_cmnds(head);
	return (0);
}

int	prepare_execution(t_cmnd *head, t_env **env, char **envp)
{
	pid_t	pid;
	int		exit_s;
	int		status_code;
	int		command_count;

	command_count = 0;
	envp = 0; //debug
	status_code = 0;
	while (head->next)
	{
		head = head->next;
		command_count++;
	}
	if (command_count == 0 && head->built_ptr)
		return (exit_status("set", execute_one(head, env)));
	pid = fork();
	if (pid == 0)
		fork_loop(&head, *env);
	else
		waitpid(pid, &exit_s, 0);
	if (WIFEXITED(exit_s))
		status_code = WEXITSTATUS(exit_s);
	exit_status("set", status_code);
	return (0);
}

int	execute_one(t_cmnd *node, t_env **env)
{
	int	ret;
	int	fd[2];

	ret = 0;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (node->redirs.o_r_type != 0)
		dup2(node->redirs.o_fd, STDOUT_FILENO);
	if (node->redirs.i_r_type != 0)
		dup2(node->redirs.i_fd, STDIN_FILENO);
	if (node->redirs.i_r_type == 3 && node->prev
		&& node->prev->redirs.o_r_type == 3)
		waitpid(node->prev->pid, NULL, 0);
	if (node->built_ptr)
		ret = node->built_ptr(*env, node->cmd);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	return (ret);
}
