/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:27:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/18 18:43:39 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int input_handle(char *input)
{
	char	**args;
	
	if (check_valid(input))
		return (1);
	args = pipe_spliter(mini_split(input));
	ft_printf("==========SPLITED==========\n");
	ft_double_print(args);
	ft_printf("===========================\n");
	ft_double_free(args);
}
