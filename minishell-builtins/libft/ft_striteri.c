/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:34:29 by abasante          #+#    #+#             */
/*   Updated: 2022/09/21 16:19:27 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f (i, &s[i]);
		i++;
	}
}

void	myfunc(unsigned int i, char *string)
{
	*string = *string + i;
}

/*
int	main(void)
{
	char str[] = "holaagur";
	printf("string sin modificar: %s\n", str);
	ft_striteri(str, myfunc);
	printf("string modificada: %s\n", str);
	return(0);
}
*/
