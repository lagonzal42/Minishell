#include "execution.h"

int		check_if_builtin(t_cmnd **node)
{
	printf("========INSIDE CHECK_IF_BUILTIN======\n");
	char	*string_in_node;

	string_in_node = ft_strdup((*node)->cmd[0]);
	if (ft_strcmp(string_in_node, "echo") == 0)
		return (1);
	else if (ft_strcmp(string_in_node, "cd") == 0)
		return (1);
	else if (ft_strcmp(string_in_node, "env") == 0)
		return (1);
	else if (ft_strcmp(string_in_node, "exit") == 0)
		return (1);
	else if (ft_strcmp(string_in_node, "export") == 0)
		return (1);
	else if (ft_strcmp(string_in_node, "pwd") == 0)
		return (1);
	else if (ft_strcmp(string_in_node, "unset") == 0)
		return (1);
	else
		return (0);
	free(string_in_node);
}
