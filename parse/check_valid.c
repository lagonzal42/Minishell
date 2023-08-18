/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:36:02 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/18 18:43:26 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_forbidden_chars(char *s)
{
	int	n;

	n = -1;
	while (s[++n])
	{
		if (s[n] == '\\' || s[n] == '`' || !ft_isascii(s[n]))
		{
			ft_printf("Minishell no gestiona el caracter %c\n", s[n]);
			return (1);
		}
		else if (s[n] == '\"')
			n += find_d_quoute_end(&s[n]);
		else if (s[n] == '\'')
			n += find_quoute_end(&s[n]);
		
	}
}