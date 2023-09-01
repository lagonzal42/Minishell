/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:36:02 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/01 16:18:33 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_forbidden_chars(char *s);
int	check_opened_quoutes(char *s);
int	ft_error(int ecode);

int	check_valid(char *s)
{
	if (check_forbidden_chars(s))
		return (1);
	if (check_opened_quoutes(s))
		return (1);
	if (ft_strnstr(s, "&&", ft_strlen(s)) || ft_strnstr(s, "||", ft_strlen(s)))
		return (ft_error(4));
	return (0);
}

int	check_forbidden_chars(char *s)
{
	int	n;

	n = -1;
	while (s[++n])
	{
		if (s[n] == '\\' || s[n] == '`' || s[n] == ';')
			return (ft_error(1));
		else if (!ft_isascii(s[n]))
		{
			return (ft_error(2));
		}
		else if (s[n] == '\"')
			n += find_d_quoute_end(&s[n]);
		else if (s[n] == '\'')
			n += find_quoute_end(&s[n]);
	}
	return (0);
}

int	check_opened_quoutes(char *s)
{
	int	n;

	n = -1;
	while (s[++n])
	{
		if (s[n] == '\"')
		{
			n += find_d_quoute_end(&s[n]);
			if (s[n] != '\"')
				return (ft_error(3));
		}
		if (s[n] == '\'')
		{
			n += find_quoute_end(&s[n]);
			if (s[n] != '\'')
				return (ft_error(3));
		}
	}
	return (0);
}

int	ft_error(int ecode)
{
	ft_putstr_fd("Error: ", 2);
	if (ecode == 1)
		ft_putstr_fd("Minishell no acepta los caracteres \"\\, ;, `\"\n", 2);
	else if (ecode == 2)
		ft_putstr_fd("Caracter no valido\n", 2);
	else if (ecode == 3)
		ft_putstr_fd("Minishell no acepta comillas sin cerrar\n", 2);
	else if (ecode == 4)
		ft_putstr_fd("Minishell no acepta los cadenas \"&& o ||\"\n", 2);
	return (1);
}
