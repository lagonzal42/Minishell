#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../builtins/builtins.h"

int		check_if_path_absolute(char *cmd);
int		execute_commands_path(char *path_name, char **av, char **envp);
int		check_if_access(char *holder);

#endif
