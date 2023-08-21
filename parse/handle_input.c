/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:27:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/21 13:53:19 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int input_handle(char *input)
{
	char	**args;
	int	n = 0;
	
	if (check_valid(input))
		return (1);
	args = mini_split(input);
	ft_printf("============MINI============\n");
	ft_double_print(args);
	while (args[n])
	{
		ft_printf("args[%d] len : %d\n", n, ft_strlen(args[n]));
		n++;
	}
	ft_printf("============================\n");
	args = pipe_spliter(args);
	ft_printf("============PIPE============\n");
	ft_double_print(args);
	ft_printf("============================\n");
	ft_double_free(args);
	return (0);
}
