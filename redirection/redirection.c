/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:45:08 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/14 14:19:31 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <fcntl.h>

static int	get_heredoc_redir(t_cmnd **tmp, char *holder);

int	get_i_redir(char *holder, t_cmnd **tmp)
{
	ft_printf("HOLDER IS: %s\n", holder); //debug
	if (ft_strlen(holder) == 0)
		return ( free(holder), 1);
	if ((*tmp)->redirs.i_r_type == 2)
		return (get_heredoc_redir(tmp, holder));
	ft_printf("input simple redir case %s\n", holder); //debug
	(*tmp)->redirs.i_fd = open(holder, O_RDONLY,  0777);
	if ((*tmp)->redirs.i_fd == -1)
		return (ft_printf("error on open:"), 1);
	ft_printf("fd name is: %s\n", holder);  //debug
	return (free(holder), 0);
}

static int	get_heredoc_redir(t_cmnd **tmp, char *holder)
{
	int		diff;
	int		fd[2];
	char	*input;
	
	ft_printf("Input heredoc case\n"); //debug
	diff = 1;
	if (pipe(fd) == -1)
		return (1);
	(*tmp)->redirs.i_fd = fd[0];
	while (diff != 0)
	{
		input = get_next_line(0);
		if (ft_strncmp(holder, input, ft_strlen(holder)) == 0)
			diff = 0;
		else
		{
			ft_printf("input was: %s", input); //debug
			ft_putstr_fd(input, fd[1]);
		}
		free (input);
	}
	close(fd[1]);
	free(holder); //optional to free here
	holder = NULL;
	return (0);	
}

int	get_o_redir(char *holder,  t_cmnd **tmp)
{

	ft_printf("output redir case %s\n", holder); //debug
	ft_printf("a\n");
	if (ft_strlen(holder) == 0)
	{
		ft_printf("strlen = 0\n"); //debug
		return(free(holder), 1);
	}
	ft_printf("a\n");
	if ((*tmp)->redirs.o_r_type == 1)
		(*tmp)->redirs.o_fd = open(holder, O_WRONLY | O_CREAT| O_TRUNC, 0644);
	else if ((*tmp)->redirs.o_r_type == 2)
		(*tmp)->redirs.o_fd = open(holder, O_WRONLY | O_CREAT | O_APPEND);
	ft_printf("fd name is: %s\n", holder); //debug
	return(free(holder), (*tmp)->redirs.o_fd == -1);
}

int pipe_case(t_cmnd **tmp)
{
	ft_printf("Pipe case\n"); //debug
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
