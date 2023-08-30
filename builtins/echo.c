#include "builtins.h"

int	num_of_args(char **args)
{
	int 	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int		echo(char **args)
{
	int i;
	int n_flag;

	i = 1;
	n_flag = 0;
	if (num_of_args(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			n_flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write (1, " ", 1);
			i++;
		}
	}
	if (n_flag == 0)
		write (1, "\n", 1);
	return (0);
}
