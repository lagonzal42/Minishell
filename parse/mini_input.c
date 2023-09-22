/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:39:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/21 15:55:55 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "../readline/readline.h"
#include "../readline/history.h"
#include <unistd.h>
#include "parse.h"
#include "../builtins/builtins.h"

/*This function below manages the ctrl + c signal. I don't know if we will need
to change it in the future so i wont explain it now.*/

void	siginthandle(int sigint)
{
	if (sigint == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line(); 
		rl_replace_line("", sigint);
		rl_redisplay();	
	}
}
/*This function is the start of the program, we will probably need to aply
some changes to it. But basically calls the readline function and sends
the input to the input handler. 
If an eof appears it closes the prompt line and clears the history.*/

void	minishell(t_env **env, char **envp)
{
	int		eof;
	char	*s;

	eof = 0;
	signal(SIGINT, siginthandle);
	while (!eof)
	{
		s = readline(">>> ");
		if (s)
		{
			if (*s)
			{
				input_handle(s, env, envp);
				add_history(s);
			}
			free(s);
		}
		else
		{
			//printf("it doesn't\n");
			eof = 1;
		}
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	argv = 0;
	if (argc != 1)
		return (1);
	env = NULL;
	env = get_env(envp, env);
	rl_catch_signals = 0;
	minishell(&env, envp);
	return (0);
}
