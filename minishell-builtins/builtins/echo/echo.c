//#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
int	ft_strcmp(const char *s1, const char *s2);

int	num_of_args(char **args)
{
	int 	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

// void	ft_putstr_fd(char *s, int fd)
// {
// 	unsigned int	len;
// 	unsigned int	i;

// 	i = 0;
// 	len = ft_strlen(s);
// 	while (i < len)
// 	{
// 		write(fd, &s[i], 1);
// 		i++;
// 	}
// }

// int	ft_strlen(const char *str)
// {
// 	int	n;

// 	n = 0;
// 	while (str[n] != '\0')
// 	{
// 		n++;
// 	}
// 	return (n);
// }

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
