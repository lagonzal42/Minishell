/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:54:01 by larra             #+#    #+#             */
/*   Updated: 2023/09/01 16:47:45 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../parse/parse.h"

int	find_end_word(char **spltd, int n, int m)
{
	int	k;

	k = m;
	m++;
	while (spltd[n][m] && (!ft_is_space(spltd[n][m]) && spltd[n][m] != '>' &&
		spltd[n][m] != '<' && spltd[n][m] != '|' && spltd[n][m] != '\"' &&
		spltd[n][m] != '&' && spltd[n][m] != '\\' && spltd[n][m] != '\'' &&
		spltd[n][m] != '$'))
		m += 1;
	return (m - k);
}

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
