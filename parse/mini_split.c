/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larra <larra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:09:10 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/02 18:37:38 by larra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parse.h"
#include <stdio.h>

static int		mini_wc(char *trimed);
static void		separate(char *s, char **spltd, int n, int j);

/*This function counts the words taking into account the quoutes
- Input: The prompt from readline but with no spaces in the beggining
		nor the end.
- Return: word is the quantity of arrays that we need to hold our prompt*/

static int	mini_wc(char *trimed)
{
	int		n;
	char	word;

	n = 0;
	word = 0;
	while (trimed[n])
	{
		if (trimed[n] != ' ' && (n == 0 || trimed[n - 1] == ' '))
			word++;
		if (trimed[n] == '\'' && (n == 0 || trimed[n - 1] != 92))
			n += find_quoute_end(&trimed[n]);
		else if (trimed[n] == '\"' && (n == 0 || trimed[n - 1] != 92))
			n += find_d_quoute_end(&trimed[n]);
		n++;
	}
	return (word);
}

/*This function makes the different arrays that will be 
created without spaces
- Input: the trimmed prompt: s; the place to hold the splitted prompt: spltd
		the words counted in the previous function: n; an integer to use in
		the function to move into spltd: j*/

void	separate(char *s, char **spltd, int n, int j)
{
	int	start;

	start = 0;
	j = 0;
	while (s[start] && j < n)
	{
		if (ft_is_space(s[start]))
			start++;
		else
		{
			spltd[j] = ft_substr(s, start,
					ft_find_space(&s[start]) - &s[start] + 1);
			start += ft_strlen(spltd[j++]);
		}
	}
}

/*This function works like a normal split, first it counts words,
then allocates memory, and then uses that memory to save the splited
prompt. It also trims twice just in case, but i think its unnecessary.
-Input: The prompt from readline: s
-Output: The prompt without spaces and splitted by them.*/

char	**mini_split(char *s)
{
	char	**spltd;
	char	*trimed;
	int		n;

	trimed = ft_strtrim(s, " ");
	n = mini_wc(trimed);
	spltd = malloc((n + 1) * sizeof(char *));
	separate(s, spltd, n, 0);
	spltd[n] = NULL;
	ft_multitrim(spltd, " ");
	free(trimed);
	return (spltd);
}

/*int main(int argc, char **argv)
{
	char *s;
	
	s = argv[1];
	printf("String is :%s\n", s);
	mini_split(s);
}*/
