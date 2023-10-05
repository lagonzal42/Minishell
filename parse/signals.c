/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:57:13 by lagonzal          #+#    #+#             */
/*   Updated: 2023/10/05 18:30:57 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "../readline/readline.h"
#include "../readline/history.h"
#include "../expand/expand.h"
#include "parse.h"

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

void	sigquithandle(int sigquit)
{
	if (interactivity(0) == 1)
		;
	else if (interactivity(0) == 2)
	{
		ft_putstr_fd("Quit\n", 2);
	}
	(void)sigquit;
}

void	call_signals(void)
{
	signal(SIGINT, siginthandle);
	signal(SIGQUIT, sigquithandle);
}
