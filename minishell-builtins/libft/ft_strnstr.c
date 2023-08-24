/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:39:05 by abasante          #+#    #+#             */
/*   Updated: 2022/09/19 17:46:43 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack [i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// #include "libft.h"

// int	main(void)
// {
// 	char haystack[30] = "hola mundo";
// 	char needle[10] = "mun";

// //	ft_strnstr(haystack, needle, -1) == haystack + 1

// //	strcpy(ret1, strnstr(str, find1, 15));
// 	printf("str_lib >> %s \n", strnstr(haystack, needle, 20));
// //	strcpy(ret2, strnstr(str, find2, 15));
// 	printf("str_ft >> %s \n", ft_strnstr(haystack, needle, 20));

// 	return (0);
// }
