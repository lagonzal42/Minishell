/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:54:01 by larra             #+#    #+#             */
/*   Updated: 2023/09/04 19:38:13 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../parse/parse.h"

/*This function finds the  "end of the word" for expanding. I limited the 
word using spaces and metacharacters such as "<, >, |, ", ', &, \ and $". 
I'm not sure if this is complete, maybe theres something missing but it works
properly so we can update it.
-Input: spltd: the comand line splitted array; n: first reference to pointer;
		m: second reference to pointer.
-Output: the length of the word*/

int	find_end_word(char **spltd, int n, int m)
{
	int	k;

	k = m;
	while (spltd[n][m] && (!ft_is_space(spltd[n][m]) && spltd[n][m] != '>' &&
		spltd[n][m] != '<' && spltd[n][m] != '|' && spltd[n][m] != '\"' &&
		spltd[n][m] != '&' && spltd[n][m] != '\\' && spltd[n][m] != '\'' &&
		spltd[n][m] != '$'))
		m += 1;
	return (m - k);
}
/*This function takes an string and it deletes the quoutes
that are in start and en position. It splits into 3 strings and rejoins without
quoutes.
-Input: spltd: part of comand line string; end: position of the closing quoute;
		start: position of the opening quoute.
-Output: The string without the quoutes*/

char	*trim_quoutes(char *spltd, int end, int start)
{
	char	*left;
	char	*right;
	char	*mid;
	char	*ret;

	left = ft_substr(spltd, 0, start);
	mid = ft_substr(spltd, start + 1, end - 1);
	right = ft_substr(spltd, start + end + 1, ft_strlen(spltd));
	ret = ft_strjoin(ft_strjoin(left, mid), right);
	return (free(left), free(mid), free(right), ret);
}

/*This function finds the quoutes in the strings from the array that gets as
an input and trims them.
-Input: spltd: a double array.
-Output: The same array but with the quoutes trimmed.*/

char	**quit_quoutes(char **spltd)
{
	int		n;
	int		m;
	int		end;

	n = -1;
	while (spltd[++n])
	{
		m = 0;
		while (spltd[n][m])
		{
			if (spltd[n][m] == '\"' || spltd[n][m] == '\'')
			{
				if (spltd[n][m] == '\'')
					end = find_quoute_end(&spltd[n][m]);
				else
					end = find_d_quoute_end(&spltd[n][m]);
				spltd[n] = trim_quoutes(spltd[n], end, m);
				m += end -1;
			}
			else
				m++;
		}
	}
	return (spltd);
}
