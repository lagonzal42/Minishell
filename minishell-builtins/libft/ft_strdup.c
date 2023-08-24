/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:36:50 by abasante          #+#    #+#             */
/*   Updated: 2022/09/19 18:00:07 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char	*ft_strdup(const char *s1)
{
	int		cont;
	char	*s1_new;
	int		size;

	size = ft_strlen (s1);
	s1_new = malloc (sizeof(char) * size + 1);
	if (!s1_new)
		return (NULL);
	cont = 0;
	while (s1[cont] != '\0')
	{
		s1_new[cont] = s1[cont];
		cont++;
	}
	s1_new[cont] = s1[cont];
	return (s1_new);
}

// int main(void)
// {
// 	printf ("%s\n", ft_strdup("hola Mundo!!"));
// 	printf ("%s\n", strdup("hola Mundo!!"));
// 	return (0);
// }
