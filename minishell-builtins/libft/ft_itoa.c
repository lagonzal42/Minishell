/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasante <abasante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:59:47 by abasante          #+#    #+#             */
/*   Updated: 2022/09/26 12:42:24 by abasante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_length(int n_length)
{
	int	length;

	length = 1;
	while (n_length / 10 != 0)
	{
		length++;
		n_length = n_length / 10;
	}
	if (n_length < 0)
		length = length + 1;
	return (length);
}

char	*ft_itoa(int n)
{
	char	*strnum;
	int		counter;
	int		str_length;
	long	nb;

	nb = n;
	str_length = ft_length(nb);
	strnum = (char *)malloc(sizeof(char) * (str_length + 1));
	if (!(strnum))
		return (NULL);
	strnum[str_length] = '\0';
	counter = 0;
	if (nb < 0)
	{
		strnum[counter] = '-';
		nb = nb * -1;
	}	
	if (nb == 0)
		strnum[0] = '0';
	while (nb > 0)
	{
		strnum[str_length - counter++ - 1] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (strnum);
}
