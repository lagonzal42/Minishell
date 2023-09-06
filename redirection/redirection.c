/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:45:08 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/06 17:10:27 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <fcntl.h>

static int	get_heredoc_redir(char **spltd, t_cmnd **tmp, char *holder);

int	get_i_redir(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	char *holder;

	if ((*tmp)->redirs.i_r_type)
		close_previous_in(tmp);
	if (spltd[*n][*m] == spltd[*n][*m + 1])
		(*tmp)->redirs.i_r_type = 2;
	else
		(*tmp)->redirs.i_r_type = 1;
	while (spltd[*n][*m] == '<')
		*m += 1;
	if (spltd[*n][*m] == '\0')
	{
		*n += 1;
		*m = 0; 
	}
	holder = ft_substr(&spltd[*n][*m], 0, find_next_meta(&spltd[*n][*m]));
	if (ft_strlen(holder) == 0)
		return (redir_error(spltd[*n][*m]), free(holder), 1);
	if ((*tmp)->redirs.i_r_type == 2)
		return (*m += ft_strlen(holder) - 1, get_heredoc_redir(spltd, tmp, holder));
	ft_printf("input simple redir case %s\n", &spltd[*n][*m]); //debug
	(*tmp)->redirs.i_fd = open(holder, O_RDONLY);
	if ((*tmp)->redirs.i_fd == -1)
		return (perror("open:"), 1);
	printf("fd name is: %s\n", holder);  //debug
	return (*m += ft_strlen(holder) - 1, free(holder), 0);
}

static int	get_heredoc_redir(char **spltd, t_cmnd **tmp, char *holder)
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
			ft_printf("input was: %s\n", input); //debug
			ft_putstr_fd(input, fd[1]);
			free (input);
		}
	}
	close(fd[1]);
	free(holder);
	return (0);	
}

int	get_o_redir(char **spltd, int *n, int *m, t_cmnd **tmp)
{
	char *holder;

	ft_printf("output redir case %s\n", &spltd[*n][*m]); //debug
	if ((*tmp)->redirs.o_r_type)
		close((*tmp)->redirs.o_fd);
	if (spltd[*n][*m] == spltd[*n][*m + 1])
		(*tmp)->redirs.i_r_type = 2;
	else
		(*tmp)->redirs.i_r_type = 1;
	while (spltd[*n][*m] == '>')
		*m += 1;
	if (spltd[*n][*m] == '\0')
	{
		*n += 1;
		*m = 0; 
	}
	if (spltd[*n][*m] == '\"' || spltd[*n][*m] == '\'')
		*m += 1;
	holder = ft_substr(&spltd[*n][*m], 0, find_next_meta(&spltd[*n][*m]));
	if (ft_strlen(holder) == 0)
		return(redir_error(spltd[*n][*m]), free(holder), 1);
	else if ((*tmp)->redirs.o_r_type == 1)
		(*tmp)->redirs.o_fd = open(holder, O_WRONLY | O_CREAT| O_TRUNC);
	else if ((*tmp)->redirs.o_r_type == 2)
		(*tmp)->redirs.o_fd = open(holder, O_WRONLY | O_CREAT | O_APPEND);
	printf("fd name is: %s\n", holder); //debug
	return(*m += ft_strlen(holder) - 1, free(holder), (*tmp)->redirs.o_fd == -1);
}

int pipe_case(t_cmnd **tmp)
{
	ft_printf("Pipe case\n");
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
		(*tmp)->redirs.o_fd = fd[0];
		(*tmp)->redirs.o_r_type = 3;
	}
	*tmp = (*tmp)->next;
	(*tmp)->redirs.i_r_type = 3;
	(*tmp)->redirs.i_fd = fd[1];
	return (0);
}