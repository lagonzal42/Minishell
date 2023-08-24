/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:56:43 by abasante          #+#    #+#             */
/*   Updated: 2022/09/14 17:12:20 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	y1;
	unsigned int	y2;
	unsigned int	i;
	unsigned int	x;
	char			*str1;

	if (!s1 || !s2)
		return (0);
	y1 = ft_strlen(s1);
	y2 = ft_strlen(s2);
	i = 0;
	x = -1;
	str1 = malloc(sizeof(char) * (y1 + y2 + 1));
	if (!str1)
		return (0);
	while (s1[i])
	{
		str1[i] = s1[i];
		i++;
	}
	while (s2[++x])
		str1[i++] = s2[x];
	str1[i] = '\0';
	return (str1);
}

// int main(void)
// {
// 	char primero[] = "hello";
// 	char segundo[] = "hola";

// 	printf("%s\n", ft_strjoin(primero, segundo));
// 	return(0);
// }
