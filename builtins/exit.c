#include "builtins.h"

int	exit_builtin(t_env *env, char **cmd)
{
	env = 0;
	cmd = 0;
	exit(0);
}
