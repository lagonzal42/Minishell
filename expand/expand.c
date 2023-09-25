/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:16:20 by lagonzal          #+#    #+#             */
/*   Updated: 2023/09/25 15:03:25 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "../libft/libft.h"
#include "../parse/parse.h"
#include <stdarg.h>
#include "expand.h"
#include <string.h>

char	**quoute_case(char **spltd, int n, int *m, t_env *env);
char	**dollar_case(char **spltd, int n, int *m, t_env *env);

/*This function has an static variable to manage the exit status. We
need it in order to have the exit codes of the comands that we execute.
- Input: action: this is going to have to options (set and get). If we use get
		it returns the last exit status of the last thing that was executed. If
		we use set it sets the static variable to the new exit status code.
		It is suposed to be a second varible in the input in the set case, the
		new error code.
- Output: it returns the value of the static variable in the get case and 0 in
		the set case.*/

int	exit_status(char *action, ...)
{
	static int	e_status;
	va_list		arg_ptr;

	if (action[0] == 'g')
		return (e_status);
	else
	{
		va_start(arg_ptr, action);
		e_status = va_arg(arg_ptr, int);
		return (0);
	}		
}

/*This function looks for expanding cases. If a simple quoute appears it simply
jumps to the end of it. If there is a double quoute or a dollar sign it goes to
the function that manages that case.
-Input: spltd: the splitted array of that comes from de comand line; 
		env: a pointer to the head of our enviroment linked list
-Output: The array with the modifications if there has been any.*/

char	**expand(char **spltd, t_env *env)
{
	int	n;
	int	m;

	n = 0;
	while (spltd[n])
	{
		m = 0;
		while (spltd[n][m])
		{
			if (spltd[n][m] == '\"')
				spltd = quoute_case(spltd, n, &m, env);
			else if (spltd[n][m] == '$')
				spltd = dollar_case(spltd, n, &m, env);
			else if (spltd[n][m] == '\'')
				m += find_quoute_end(&spltd[n][m]);
			if (spltd[n][m] != '$')
				m++;
		}
		n++;
	}
//	quit_quoutes(spltd);
	return (spltd);
}

/*This fucntion looks for any dollar that appears before the end of the quoutes.
input,
- Input: spltd: the comand line array; n: the first pointers reference;
		m: a pointer to the variable of the second pointers reference
		(i use a pointer in order to be able to modify it, this way i dont
		check some positions twice); env: a pointer to the enviroment linked
		list.
-Output: The array with the modifications if there has been any.*/

char	**quoute_case(char **spltd, int n, int *m, t_env *env)
{
	*m += 1;
	while (spltd[n][*m] && spltd[n][*m] != '\"')
	{
		if (spltd[n][*m] == '$')
			spltd = dollar_case(spltd, n, m, env);
		else
			*m += 1;
	}
	return (spltd);
}

/*This function checks for the name of the variable that has to be expanded.
Then divides de array in three: name, left and right. After that checks how to
expand the name. If it is ? gets the last exit status, otherwise takes
the value from the enviroment list. If the variable to be expanded doesn't
exist it returns nothing and nothing will be between left and right.
In the end it joins everything again and substitutes the not expanded one
in the array for the new one with the expansion.
- Input: spltd: The spltd array; n: first reference to pointer;
		m: second reference to pointer; env = pointer to enviroment linked
		list.
- Output: The new array with the proper expansion for each case.*/

char	**dollar_case(char **spltd, int n, int *m, t_env *env)
{
	int		prev;
	char	*holder;
	char	*name;
	char	*to_add[4];

	prev = *m;
	name = ft_substr(spltd[n], *m + 1, find_end_word(spltd, n, *m + 1));
	to_add[0] = ft_substr(spltd[n], 0, *m);
	to_add[2] = ft_substr(spltd[n], *m + ft_strlen(name) + 1,
			ft_strlen(spltd[n]));
	if (ft_strncmp(name, "?", 1) == 0)
		to_add[1] = ft_itoa(exit_status("get"));
	else
		to_add[1] = ft_strdup(search_for_var(env, name));
	to_add[3] = ft_strjoin(to_add[1], to_add[2]);
	holder = ft_strjoin(to_add[0], to_add[3]);
	free(spltd[n]);
	spltd[n] = holder;
	return (free(to_add[0]), free(to_add[1]), free(to_add[2]), spltd);
}

/*int	main(int ac, char **av, char **envp)
{
	t_env	*enviroment;

	enviroment = get_env(envp, enviroment);
	char *spltd[] = {"$U$U$USER", NULL};
	char **new;
	printf("==============PREV================\n");
	ft_double_print(spltd);
	printf("==============PREV================\n");
	new = expand(spltd, enviroment);
	printf("==============FINAL================\n");
	ft_double_print(new);
	printf("==============FINAL================\n");
}*/