/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:43:23 by abasante          #+#    #+#             */
/*   Updated: 2022/09/19 15:12:08 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*strsub;

	if (len > (size_t)ft_strlen(s))
	{
		len = ft_strlen(s);
	}
	strsub = (char *)malloc(len + 1);
	if (start > (unsigned int)ft_strlen(s))
	{
		*strsub = '\0';
		return (strsub);
	}
	if (!strsub)
	{
		return (0);
	}
	ft_strlcpy(strsub, &s[start], len + 1);
	return (strsub);
}

/*
int main(void)
{
	char	*s;

	s = "hola buenas tardes";
	
	printf("%s\n", ft_substr(s, 5, 8));
}
*/