/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:01:03 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/01 16:19:54 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/*===============================REDIRECTIONS=================================*/
# define NO_REDIR 0
# define PIPE_REDIR 1
# define SIMPLE_REDIR 2
# define DOUBLE_REDIR 3

# define BACK_SLASH 92

# define STD_OUT 1
# define STD_IN 0

# include "../libft/libft.h"
# include "../expand/expand.h"
# include "../builtins/builtins.h"

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
	struct s_cmnd	*next;
	struct s_cmnd	*prev;
	struct s_redir	redirs;
}	t_cmnd;

t_cmnd	*parse(char *s);
int		find_quoute_end(char *trimed);
int		find_d_quoute_end(char *trimed);
char	**pipe_spliter(char **in);
char	**mini_split(char *s);
int		input_handle(char *input, t_env *env);
int		check_valid(char *s);
char	*ft_find_space(char *s);

#endif
