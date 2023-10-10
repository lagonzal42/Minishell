/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoute_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:21:36 by larra             #+#    #+#             */
/*   Updated: 2023/10/10 13:47:23 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse/parse.h"
#include "../expand/expand.h"

static int	quoute_detector(char *s);

char	*q_t(char *s)
{
	int	start;
	int	end;

	start = 0;
	while (quoute_detector(s))
	{
		while (s[start] != '\"' && s[start] != '\'')
			start++;
		if (s[start] == '\'')
			end = start + find_quoute_end(&s[start]);
		if (s[start] == '\"')
			end = start + find_d_quoute_end(&s[start]);
		s = trim_quoutes(s, start, end);
	}
	return (s);
}

int	find_first_quoute(char *s, int *q, int *n)
{
	while (s[*n] && !*q)
	{
		if (s[*n] == '\"')
			*q = 2;
		else if (s[*n] == '\'')
			*q = 1;
		else
			*n += 1;
	}
	return (*q);
}

static int	quoute_detector(char *s)
{
	int	n;
	int	q;
	int	fin;

	q = 0;
	n = 0;
	find_first_quoute(s, &q, &n);
	if (q == 2)
	{
		fin = n + find_d_quoute_end(&s[n]);
		return (s[fin] == '\"');
	}
	if (q == 1)
	{
		fin = n + find_quoute_end(&s[n]);
		return (s[fin] == '\'');
	}
	return (0);
}

// int	main(void)
// {
// 	char	*s;
// 	char	*result;

// 	s = ft_strdup("\"\"\"\"");
// 	result = q_t(s);
// 	ft_printf("s: %s\nresult: %s\n", s, result);
// 	//free(s);
// 	free(result);

// }