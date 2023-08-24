/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larra <larra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:16:20 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/24 15:01:23 by larra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../parse/parse.h"
#include "expand.h"
#include <stdio.h>

char	**quoute_case(char **spltd, int n, int *m);
char	**dollar_case(char **spltd, int n, int *m, int quoute);

char	**expand(char **spltd)
{
	int n;
	int m;

	n = 0;
	while (spltd[n])
	{
		m = 0;
		while (spltd[n][m])
		{
			if (spltd[n][m] == '\"')
				spltd = quoute_case(spltd, n, &m);
			else if (spltd[n][m] == '$')
				spltd = dollar_case(spltd, n, &m, 0);
			m++;
		}
		n++;
	}
	return (spltd);
}

char	**quoute_case(char **spltd, int n, int *m)
{
	*m += 1;
	while (spltd[n][*m] && spltd[n][*m] != '\"')
	{
		if (spltd[n][*m] == '$')
			spltd = dollar_case(spltd, n, m, 1);
		else
			*m += 1;
	}
	return (spltd);
}

char **dollar_case(char **spltd, int n, int *m, int quoute)
{
	int		prev;
	char	*holder;
	char	*left;
	char	*right;
	char	*name;

	prev = *m;
	printf("from prev: %s\n", &spltd[n][*m]);
	name = ft_substr(spltd[n], *m + 1, find_end_word(spltd, n, *m + 1));
	ft_printf("name to expand :%s\n", name);
	left = ft_substr(spltd[n], 0, *m);
	right = ft_substr(spltd[n], *m + find_end_word(spltd, n, *m), ft_strlen(spltd[n]));
	printf("left %s\n", left);
	printf("right %s\n", right);
	*m += ft_strlen(name);
	free(name);
	free(left);
	free(right);
	return (spltd);
}


int	main(void)
{
	char *spltd[] = {"echo", "\"my asingment is to write de user: $USER|mi_file TASK COMPLETED!\"", "|", "cat", "-e", NULL};
	expand(spltd);
}