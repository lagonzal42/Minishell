/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:45:08 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/22 18:24:27 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <fcntl.h>
#include <stdlib.h>
#include "../readline/readline.h"
#include "../readline/history.h"


static int	get_heredoc_redir(t_cmnd **tmp, char *holder);

int	get_i_redir(char *holder, t_cmnd **tmp)
{
	if (!holder)
		return (1);
	if (ft_strlen(holder) == 0)
		return (free(holder), 1);
	if ((*tmp)->redirs.i_r_type == 2)
		return (get_heredoc_redir(tmp, holder));
	(*tmp)->redirs.i_fd = open(holder, O_RDONLY, 0777);
	if ((*tmp)->redirs.i_fd == -1)
		return (ft_printf("error on open:"), 1);
	return (free(holder), 0);
}

static int	get_heredoc_redir(t_cmnd **tmp, char *holder)
{
	int		diff;
	int		fd[2];
	char	*input;

	diff = 1;
	if (pipe(fd) == -1)
		return (1);
	while (diff != 0)
	{
		input = readline(">");
		if (!input || ft_strncmp(holder, input, ft_strlen(holder)) == 0)
			diff = 0;
		else
			ft_putendl_fd(input, fd[1]);	
		free (input);
	}
	close(fd[1]);
	holder = NULL;
	return ((*tmp)->redirs.i_fd = fd[0], free(holder), 0);
}

int	get_o_redir(char *holder, t_cmnd **tmp)
{
	if (!holder)
		return (1);
	if (ft_strlen(holder) == 0)
		return (free(holder), 1);
	if ((*tmp)->redirs.o_r_type == 1)
		(*tmp)->redirs.o_fd = open(holder, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*tmp)->redirs.o_r_type == 2)
		(*tmp)->redirs.o_fd = open(holder, O_WRONLY | O_CREAT | O_APPEND);
	return (free(holder), (*tmp)->redirs.o_fd == -1);
}

int	pipe_case(t_cmnd **tmp)
{
	int		fd[2];
	t_cmnd	*new;

	if (pipe(fd) == -1)
		return (1);
	new = cmnd_init();
	if (!new)
		return (2);
	(*tmp)->next = new;
	if ((*tmp)->redirs.o_r_type == 0)
	{
		(*tmp)->redirs.o_fd = fd[1];
		(*tmp)->redirs.o_r_type = 3;
	}
	(*tmp)->next->prev = (*tmp);
	*tmp = (*tmp)->next;
	(*tmp)->redirs.i_r_type = 3;
	(*tmp)->redirs.i_fd = fd[0];
	return (0);
}
