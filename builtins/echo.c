#include "builtins.h"

int	num_of_args(char **args)
{
	int 	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int		check_if_nnnn(char *args)
{
	int	i;

	i = 1;
	if (args[0] == '-')
	{
		while (args[i] == 'n')
			i++;
		if (args[i] == '\0')
			return (0);
		else
			return (1);
	}
	return (1);
}

int		echo(t_env *env, char **args)
{
	int i;
	int	a;
	int n_flag;

	env = 0;
	a = 0;
	i = 1;
	n_flag = 1;
	while (num_of_args(args) > 1 && args[i])
	{
			if (check_if_nnnn(args[i]) == 0 && a == 0)
				n_flag = 0;
			else
			{
				a = 1;
				ft_putstr_fd(args[i], 1);
				if (args[i + 1])
					write (1, " ", 1);
			}
			i++;
	}
	if (n_flag == 1)
		write (1, "\n", 1);
	return (0);
}
