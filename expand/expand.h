/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larra <larra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:19:45 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/07 10:32:15 by larra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include"../builtins/builtins.h"

int		find_end_word(char **spltd, int n, int m);
int		exit_status(char *action, ...);
char	**expand(char **spltd, t_env *env);
char	**quit_quoutes(char **spltd);
char	*trim_quoutes(char *spltd, int end, int start);

#endif