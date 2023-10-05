/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:01:03 by lagonzal          #+#    #+#             */
/*   Updated: 2023/10/05 18:31:46 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/*===============================REDIRECTIONS================================*/
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

int		input_handle(char *input, t_env **env, char **envp);

/*============================CALLED BY INPUT HANDLER========================*/

int		check_valid(char *s);
char	**mini_split(char *s);
char	**pipe_spliter(char **in);

/*=====================================UTILS=================================*/

int		find_quoute_end(char *trimed);
int		find_d_quoute_end(char *trimed);
char	*ft_find_space(char *s);
void	free_env(t_env *env);

/*=================================SIGNALS=============*/

void	call_signals(void);
int		interactivity(int num);

#endif
