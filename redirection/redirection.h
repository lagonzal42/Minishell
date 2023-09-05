/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:56:55 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/05 17:45:36 by lagonzal         ###   ########.fr       */
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
int		cmd_create(char **spltd, t_cmnd **head);
void	redir_error(char c);
void	close_previous_in(t_cmnd **tmp);
int	add_cmd(char *spltd, int *m, t_cmnd **tmp)

#endif