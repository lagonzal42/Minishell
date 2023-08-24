/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otxoboy <otxoboy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:42:21 by abasante          #+#    #+#             */
/*   Updated: 2023/08/13 19:11:08 by otxoboy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*pt_src;

	pt_src = (char *)src;
	i = 0;
	if (dstsize > 0)
	{
		while (pt_src[i] && i < dstsize - 1)
		{
			dst[i] = pt_src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}


// #include <string.h>
// #include <stdio.h>
// #include "libft.h"

// int	main(void)
// {
// 	const char	*str = "Hello!";
// 	char		dst2[42];
// 	int			ret2;

// 	ret2 = (int)ft_strlcpy(dst2, str, 5);
// 	printf("str_ft >> %d \n", ret2);
// 	printf("str_lib >> %s \n", dst2);

// 	return (0);
// }
