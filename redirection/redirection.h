/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:56:55 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/13 16:17:18 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "../libft/libft.h"
#include "../builtins/builtins.h"

typedef struct s_redir
{
	int		i_r_type;
	int		o_r_type;
	int		i_fd;
	int		o_fd;
	char	*h_lim;
}	t_redir;

typedef void	(*builtin_function)(t_env *, char **);

typedef struct s_cmnd
{
	char				**cmd;
	char				*cmd_pth;
	builtin_function	built_ptr;
	int					prev_pid;
	struct s_cmnd		*next;
	struct s_cmnd		*prev;
	struct s_redir		redirs;
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