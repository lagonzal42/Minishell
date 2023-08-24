/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:06:52 by abasante          #+#    #+#             */
/*   Updated: 2022/09/20 15:57:49 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)

{
	char		*s;
	char		*d;
	size_t		i;

s = (char *)src;
d = (char *)dst;
i = 0;
	if (!dst && !src)
		return (0);
	if (d > s)
	{
		while (len-- > 0)
		{
			d[len] = s[len];
		}
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

// int     main(void)
// {
// 	char dst1[] = "Hey marvin!!";
// 	char dst2[] = "Hey marvin!!";
// 	const char src[] = "Ola";
// 	memmove(dst1, src, 3);
// 	printf("dst1 >> %s \n", dst1);
// 	ft_memmove(dst2, src, 3);
// 	printf("dst2 >> %s \n", dst2);
// 	return (0);
// }
