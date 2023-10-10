/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:39:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/10/10 14:08:23 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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

/*This function is the start of the program, we will probably need to aply
some changes to it. But basically calls the readline function and sends
the input to the input handler. 
If an eof appears it closes the prompt line and clears the history.*/

void	minishell(t_env **env, char **envp)
{
	static int		eof;
	char			*s;

	call_signals();
	interactivity(1);
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
		g_signaled = 0;
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
