/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:43:17 by abasante          #+#    #+#             */
/*   Updated: 2022/09/09 10:48:41 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

/*
int main(void)
{
	char dst1[] = "Hey marvin!!";
	char dst2[] = "Hey marvin!!";
	const char src[] = "Ola como";

	ft_memcpy(dst1, src, 3);
	printf("dst1 >> %s \n", dst1);
	ft_memcpy(dst2, src, 8);
	printf("dst2 >> %s \n", dst2);
}
*/
