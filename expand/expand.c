/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:16:20 by lagonzal          #+#    #+#             */
/*   Updated: 2023/08/29 13:33:26 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "../libft/libft.h"
#include "../parse/parse.h"
#include <stdarg.h>
#include "expand.h"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

char	**quoute_case(char **spltd, int n, int *m);
char	**dollar_case(char **spltd, int n, int *m, int quoute);


t_env *enviroment;

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
	}		
}

t_env *get_env(char **envp, t_env *env)
{
    t_env   *tmp;
    int i = 0;

    env = make_node();
    tmp = env;
    while (envp[i] != NULL)
    {
        tmp->name = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
        tmp->value = ft_substr(envp[i], ft_strchr(envp[i], '=') - envp[i] + 1,
            ft_strlen(envp[i]));
        if (envp[++i])
        {
            ft_lstadd_back(env, tmp);
            tmp->next = make_node();
            tmp = tmp->next;    
        }
    }
    return (env);
}

char	**expand(char **spltd)
{
	int n;
	int m;

	n = 0;
	while (spltd[n])
	{
		m = 0;
		while (spltd[n][m])
		{
			if (spltd[n][m] == '\"')
				spltd = quoute_case(spltd, n, &m);
			else if (spltd[n][m] == '$')
				spltd = dollar_case(spltd, n, &m, 0);
			m++;
		}
		n++;
	}
	return (spltd);
}

char	**quoute_case(char **spltd, int n, int *m)
{
	*m += 1;
	while (spltd[n][*m] && spltd[n][*m] != '\"')
	{
		if (spltd[n][*m] == '$')
			spltd = dollar_case(spltd, n, m, 1);
		else
			*m += 1;
	}
	return (spltd);
}

char **dollar_case(char **spltd, int n, int *m, int quoute)
{
	int		prev;
	char	*holder;
	char	*name;
	char	*to_add[3];

	prev = *m;
	printf("from prev: %s\n", &spltd[n][*m]);
	name = ft_substr(spltd[n], *m + 1, find_end_word(spltd, n, *m + 1));
	ft_printf("name to expand :%s\n", name);
	to_add[0] = ft_substr(spltd[n], 0, *m);
	to_add[2] = ft_substr(spltd[n], *m + find_end_word(spltd, n, *m), 
		ft_strlen(spltd[n]));
	printf("left %s\n", to_add[0]);
	printf("right %s\n", to_add[2]);
	if (open("a.txt", O_RDONLY))
		printf("not opened\n");
	if (ft_strncmp(name, "?", 1) == 0)
	 	to_add[1] = ft_itoa(exit_status("get"));
	to_add[1] = ft_strdup(search_for_var(enviroment, name));
	printf("expanded: %s\n", to_add[1]);
	*m += ft_strlen(to_add[1]) - 1;
	holder = ft_strjoin(to_add[0], ft_strjoin(to_add[1], to_add[2]));
	spltd[n] = holder;
	ft_double_print(spltd);
	return (free(to_add[0]), free(to_add[1]), free(to_add[2]), spltd);
}

int	main(int ac, char **av, char **envp)
{
	enviroment = get_env(envp, enviroment);
	char *spltd[] = {"echo", "\"my asingment is to write de user: $USER|mi_file TASK COMPLETED!\"", "|<<$USER", "$? cat", "-e", NULL};
	char **new;
	printf("==============PREV================\n");
	ft_double_print(spltd);
	printf("==============PREV================\n");
	new = expand(spltd);
	printf("==============FINAL================\n");
	ft_double_print(new);
	printf("==============FINAL================\n");
}