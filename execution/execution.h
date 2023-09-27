/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:28:07 by abasante          #+#    #+#             */
/*   Updated: 2023/09/27 13:34:23 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../builtins/builtins.h"
# include "../redirection/redirection.h"

# define APPEND 5
# define TRUNC  6

int					check_if_path_absolute(char *cmd);
char				*find_path(t_cmnd **node, t_env *env);
int					check_if_access(char *holder);
void				output_redirection(t_cmnd *node);
int					execute_commands_path(char *path_name, \
						char **av, char **envp);
t_builtin_function	check_if_builtin(t_cmnd **node);
int					before_execution(t_cmnd *node, t_env *env);
void				fork_loop(t_cmnd **node, t_env *env, char **envp);
int					slash_pos(t_cmnd **node);
char				*loop(char **bin_paths, t_cmnd **node);

#endif
