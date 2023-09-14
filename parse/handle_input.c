/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:27:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/14 12:03:08 by lagonzal         ###   ########.fr       */
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

int	input_handle(char *input, t_env *env, char **envp)
{
	char	**args;
	t_cmnd	*head;

	if (check_valid(input))
		return (1);
	args = mini_split(input);
	args = pipe_spliter(args);
	args = expand(args, env);
	ft_printf("TO CREATE COMANDS ===================\n"); //debug
	ft_double_print(args);
	ft_printf("=====================================\n");
	envp = 0; //debug
	head = cmnd_init();
	if (node_create(args, &head))
		return(free_cmnds(head), 2);
	ft_double_free(args);
	ft_printf("==============COMANDS IN NODES ARE=======================\n"); //debug
	print_commands(head);
	ft_printf("==========================================================\n"); //debug
	if (before_execution(head, env) != 0)
 		return (free_cmnds(head), 3);
	fork_loop(head, env);	
	free_cmnds(head);
	return (0);
}
