/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:27:36 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/31 00:54:00 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../builtins/builtins.h"

int input_handle(char *input, t_env *env)
{
	char	**args;
	
	if (check_valid(input))
		return (1);
	args = mini_split(input);
	args = pipe_spliter(args);
	args = expand(args, env);
	ft_printf("TO CREATE COMANDS ===================\n");
	ft_double_print(args);
	ft_printf("length: %d | direction :%p\n", ft_strlen(args[1]), args[1]);
	ft_double_free(args);
	return (0);
}
