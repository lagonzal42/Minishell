/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:19:35 by lagonzal          #+#    #+#             */
/*   Updated: 2023/10/06 13:45:08 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdio.h>

int	find_quoute_end(char *trimed)
{
	int	n;

	n = 1;
	while (trimed[n] && trimed[n] != '\'')
		n++;
	return (n);
}

int	find_d_quoute_end(char *trimed)
{
	int	n;

	n = 1;
	while (trimed[n] && trimed[n] != '\"')
	{
		n++;
	}
	return (n);
}

char	*ft_find_space(char *s)
{
	int	n;

	if (!s)
		return (NULL);
	n = 0;
	while (s[n] != '\0')
	{
		if (ft_is_space(s[n]))
			return ((char *)&s[n]);
		else if ((s[n] == '\"' || s[n] == '\'')
			&& (n == 0 || s[n - 1] != '\\'))
		{
			if (s[n] == '\"')
				n += find_d_quoute_end(&s[n]);
			else if (s[n] == '\'')
				n += find_quoute_end(&s[n]);
		}
		n++;
	}
	return ((char *)&s[n]);
}
