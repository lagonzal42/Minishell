/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larra <larra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:54:01 by larra             #+#    #+#             */
/*   Updated: 2023/08/24 15:02:00 by larra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../parse/parse.h"

int	find_end_word(char **spltd, int n, int m)
{
	int	k;

	k = m;
	while (spltd[n][m] && (!ft_is_space(spltd[n][m]) && spltd[n][m] != '>' &&
		spltd[n][m] != '<' && spltd[n][m] != '|' && spltd[n][m] != '\"' &&
		spltd[n][m] != '&' && spltd[n][m] != '\\'))
		m  += 1;
	return (m - k);
}