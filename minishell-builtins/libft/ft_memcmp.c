/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 13:37:06 by abasante          #+#    #+#             */
/*   Updated: 2022/09/21 17:22:37 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (*ps1 == *ps2 && ++i < n)
	{
		ps1++;
		ps2++;
	}
	return ((int)(*ps1 - *ps2));
}

/*
int main(void)
{
	char s1[4] = "hola";
	char s2[4] = "holb";

	printf("%d", ft_memcmp(s1, s2, 4));

	return(0);
}
*/
