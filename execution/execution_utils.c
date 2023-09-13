#include "execution.h"

void *check_if_builtin(t_cmnd **node)
{
	char	*string_in_node;

	string_in_node = ft_strdup((*node)->cmd[0]);
	if (ft_strcmp(string_in_node, "echo") == 0)
	{
		free(string_in_node);
		return (&echo);
	}
	else if (ft_strcmp(string_in_node, "cd") == 0)
	{
		free(string_in_node);
		return (&cd);
	}	
	else if (ft_strcmp(string_in_node, "env") == 0)
	{
		free(string_in_node);
		return (&print_env);
	}
	else if (ft_strcmp(string_in_node, "exit") == 0)
	{
		free(string_in_node);
		return (&exit);
	}
	else if (ft_strcmp(string_in_node, "export") == 0)
	{
		free(string_in_node);
		return (&export);
	}
	else if (ft_strcmp(string_in_node, "pwd") == 0)
	{
		free(string_in_node);
		return (&pwd);
	}
	else if (ft_strcmp(string_in_node, "unset") == 0)
	{
		free(string_in_node);
		return (&unset);
	}
	else
	{
		free(string_in_node);
		return (NULL);
	}
}
