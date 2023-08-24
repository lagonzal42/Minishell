/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:38:10 by abasante          #+#    #+#             */
/*   Updated: 2022/09/13 12:20:01 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;

	dest = malloc(size * count);
	if (!dest)
		return (NULL);
	ft_memset (dest, 0, size * count);
	return (dest);
}

/*
int	main(void)
{
	int	*pData;

	int i, n;
	printf("El numero de digitos que se introduciran:");
	scanf("%d", &i);
	pData = (int *)calloc(i, sizeof(int));
	if (pData == NULL)
		return (1);
	for (n = 0; n < i; n++)
	{
		printf ("ingresa un numero #% d:", n + 1);
		scanf ("%d", &pData[n]);
	}
	printf ("El numero que ingresaste es:");
	for (n = 0; n < i; n++)
		printf ("%d", pData[n]);
	free (pData);
	system ("pause");
	return (0);
}
*/