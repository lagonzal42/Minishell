/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:46:09 by abasante          #+#    #+#             */
/*   Updated: 2022/09/27 10:32:59 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_size_substring(char const *s, char c)
{
	size_t	i;
	size_t	numsubstr;

	i = 0;
	numsubstr = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			numsubstr++;
		}
		while (s[i] && s[i] != c)
		{
			i++;
		}
		if (s[i])
		{
			i++;
		}
	}
	return (numsubstr);
}

char	*ft_substring(char const *s, char c, size_t j)
{
	size_t	i;
	size_t	count;
	char	*str;

	str = 0;
	i = -1;
	count = -1;
	while (++i < (size_t)ft_strlen(s) && s[i])
	{
		if (s[i] != c)
			count++;
		if (count == j && s[i] != c)
		{
			count = i;
			while (s[count] && s[count] != c)
				count++;
			str = ft_substr(s, i, count - i);
			if (!str)
				return (0);
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	size_t	substring;
	size_t	i;

	if (!s)
		return (0);
	substring = ft_size_substring(s, c);
	if (c == '\0' && ft_strlen(s) > 0)
		substring = 1;
	strings = (char **)ft_calloc(substring + 1, sizeof(char *));
	if (strings == 0)
		return (0);
	i = 0;
	while (i < substring)
	{
		strings[i] = ft_substring(s, c, i);
		if (strings[i] == 0)
			return (0);
		i++;
	}
	strings[i] = 0;
	return (strings);
}
