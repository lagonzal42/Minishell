/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 11:40:27 by lagonzal          #+#    #+#             */
/*   Updated: 2023/10/05 19:18:16 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parse.h"
#include <stdio.h>

/*Splits by the current position separating in 3, the left part the pipe and
the right part. If there is no left part(pipe in first position) or there is
no right part (pipe in last position) the size of the array will be different
- Input: s: the string that will be splited in 1, 2, or 3; m: the position of
the pipe.
- Output: The array that has the s string splitted.*/

char	**spliter(char *s, int m)
{
	char	**holder;
	int		n;
	int		size;

	size = 2;
	if (m != 0)
		size++;
	if (s[m + 1])
		size++;
	holder = malloc(size * sizeof(char *));
	holder[size - 1] = NULL;
	n = 0;
	if (m != 0)
		holder[n++] = ft_substr(s, 0, m);
	holder[n++] = ft_substr(s, m, 1);
	if (s[m + 1])
		holder[n] = ft_substr(s, m + 1, ft_strlen(&s[m] + 1));
	free(s);
	return (holder);
}

/*Resizes the arrai to insert the adition in the indicated position
- Input: sp: The array that is space splited; addition: the array that is
			going to be added; pos: the position where the first element of
			addition should be placed
- Output: the resized array.*/

char	**ft_resize2(char **sp, char **addition, unsigned int pos)
{
	int		n;
	int		m;
	char	**new;

	n = 0;
	while (sp[n])
		n++;
	m = 0;
	while (addition[m])
		m++;
	new = malloc((m + n) * sizeof(char *));
	n = -1;
	while ((unsigned int)++n < pos)
		new[n] = sp[n];
	m = 0;
	while (addition[m])
		new[n++] = addition[m++];
	while (sp[++pos])
	{
		new[n] = sp[pos];
		n++;
	}
	new[n] = NULL;
	return (free(sp), free(addition), new);
}

void	ft_recount(int *n, int *m, char **sp)
{
	if (sp[*n + 1])
	{
		*n += 1;
	}
	*m = 0;
}
/*Finds pipes out of the quoutes and divides it in 3 arrays.
Then inserts it in the previous array using resize.
-Input: same as previous
-Output: the array that has the pipes in independent lines.*/

char	**ft_split_pipes(char **sp)
{
	int		n;
	int		m;
	char	**holder;

	n = 0;
	while (sp[n])
	{
		m = -1;
		while (sp[n] && sp[n][++m])
		{
			if (sp[n][m] == '\'' && (m == 0 || sp[n][m - 1] != 97))
				m += find_quoute_end(&sp[n][m]);
			else if (sp[n][m] == '\"' && (m == 0 || sp[n][m - 1] != 97))
				m += find_d_quoute_end(&sp[n][m]);
			if (sp[n][m] == '|')
			{
				holder = spliter(sp[n], m);
				sp = ft_resize2(sp, holder, n);
				ft_recount(&n, &m, sp);
			}
		}
		n++;
	}
	return (sp);
}

/*This function  calls the pipe splitter
-Input: The space splited prompt
-Output: The prompt but with the pipes splited and separated.*/

char	**pipe_spliter(char **in)
{
	char	**spltd;

	spltd = ft_split_pipes(in);
	return (spltd);
}

// int main(int argc, char **argv)
// {
// 	argc = 0;
// 	char **splited = malloc (4 * sizeof(char *));
// 	splited[0] = ft_strdup(argv[1]);
// 	splited[1] = ft_strdup(argv[2]);
// 	splited[2] = ft_strdup(argv[3]);
// 	splited[3] = NULL;
// 	splited = pipe_spliter(splited);
// 	ft_double_print(splited);
// }
