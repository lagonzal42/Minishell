/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:02:52 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/25 14:35:41 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s && s[n] != '\0')
		n++;
	return (n);
}

/*int	main(void)
{
	const char s[] = "hola fieoppqfj";
	printf("%zu\n", ft_strlen(s));
	printf("%zu\n", strlen(s));
	return (0);
}*/
