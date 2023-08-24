/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larra <larra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:19:35 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/24 15:04:20 by larra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse.h"
# include <stdio.h>

t_cmnd	*cmnd_init(void)
{
	t_cmnd	*new;

	new = malloc(sizeof(t_cmnd));
	new->cmd = NULL;
	new->redirs.i_r_type = 0;
	new->redirs.o_r_type = 0;
	new->redirs.i_fd = 0;
	new->redirs.o_fd = 1;
	new->redirs.h_lim = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
void	add_back(t_cmnd *lst, t_cmnd *new)
{
	t_cmnd *nav;

	if (!lst)
		lst = new;
	else
	{
		nav = lst;
		while (nav->next)
			nav = nav->next;
		nav->next = new;
	}
}
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
		if (trimed[n] == '\"' && trimed[n - 1] == 92)
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
		else if ((s[n] == '\"' || s[n] == '\'') && (n == 0 || s[n - 1] != '\\'))
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