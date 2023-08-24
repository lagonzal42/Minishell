/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:58:08 by abasante          #+#    #+#             */
/*   Updated: 2022/09/19 14:15:28 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest;
	size_t	orig;
	size_t	i;

	i = 0;
	orig = ft_strlen(src);
	dest = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= dest)
	{
		return (dstsize + orig);
	}
	while (i < (dstsize - dest - 1) && src[i])
	{
		dst[dest + i] = src[i];
		i++;
	}
	dst[dest + i] = '\0';
	return (dest + orig);
}

/*
int main(void)
{
	char dst[] = "holajkd";
	char src[] = "hele";
	printf("%zu", ft_strlcat(dst, src, 10));
	return(0);
}
*/