/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:39:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/10/02 17:06:11 by abasante         ###   ########.fr       */
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

int	interactivity(int num)
{
	static int	interactivity;

	if (num == 0)
		return (interactivity);
	interactivity = num;
	return (0);
}

/*This function below manages the ctrl + c signal. I don't know if we will need
to change it in the future so i wont explain it now.*/

void	siginthandle(int sigint)
{
	if (sigint == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", sigint);
		if (interactivity(0) == 1)
			rl_redisplay();
		else if (interactivity(0) == 2)
			exit_status("set", 130);
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
		s = readline("pipehell:");
		if (s)
		{
			if (*s)
			{
				interactivity(2);
				input_handle(s, env, envp);
				add_history(s);
			}
			free(s);
		}
		else
			eof = 1;
		interactivity(1);
	}
	rl_clear_history();
	free_env(*env);
}

void	free_env(t_env *env)
{
	t_env	*now;
	t_env	*prev;
	int		i;

	i = 0;
	prev = env;
	now = prev->next;
	while (now)
	{
		free(prev->name);
		free(prev->value);
		free(prev);
		prev = now;
		now = prev->next;
	}
	free(prev->name);
	free(prev->value);
	free(prev);
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
