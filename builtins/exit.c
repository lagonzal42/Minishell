#include "builtins.h"

int	exit_builtin(t_env *env, char **cmd)
{
	int ret;
	ret = 0;
	env = 0;

	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minshell: exit: too many arguments\n", STDERR_FILENO);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required", STDERR_FILENO);
	}
	else if (cmd[1])
		ret = ft_atoi(cmd[1]);
	return (ret);
}
