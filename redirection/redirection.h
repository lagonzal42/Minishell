/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <larraingonzalez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:56:55 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/08 14:27:20 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "../libft/libft.h"

typedef struct s_redir
{
	int		i_r_type;
	int		o_r_type;
	int		i_fd;
	int		o_fd;
	char	*h_lim;
}	t_redir;

typedef struct s_cmnd
{
	char			**cmd;
	char			*cmd_pth;
	int				prev_pid;
	struct s_cmnd	*next;
	struct s_cmnd	*prev;
	struct s_redir	redirs;
}	t_cmnd;

void	add_back(t_cmnd *lst, t_cmnd *new);
t_cmnd	*cmnd_init(void);
int		node_create(char **spltd, t_cmnd **head);
void	redir_error(char c);
void	close_previous_in(t_cmnd **tmp);
int		add_cmnd(char *spltd, int *m, t_cmnd **tmp);
void	print_cmnds(t_cmnd *head);
int		find_next_meta(char *spltd);
void	print_commands(t_cmnd *head);


/*========================REDIRECTION.C=========================*/

int	get_i_redir(char *holder, t_cmnd **tmp);
int	get_o_redir(char *holder, t_cmnd **tmp);
int pipe_case(t_cmnd **tmp);

/*============================UTILS============================*/

char	*q_t(char *s);
void	free_cmnds(t_cmnd *cmds);

#endif