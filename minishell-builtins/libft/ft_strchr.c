/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:03:54 by abasante          #+#    #+#             */
/*   Updated: 2023/08/14 16:56:37 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*chr;

	chr = (char *)s;
	while (*chr != (char)c)
	{
		if (!*chr)
			return (NULL);
		chr++;
	}
	return (chr);
}

// int main(void)
// {
// 	char s[50] = "This is my string";

// 	printf("%s", ft_strchr(s, 'h'));
// 	return(0);
// }
