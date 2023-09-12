#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../builtins/builtins.h"
# include "../redirection/redirection.h"

# define APPEND 5
# define TRUNC  6

int		check_if_path_absolute(char *cmd);
char	*find_path(int bon, t_cmnd **node, t_env *env);
int		check_if_access(char *holder);
void    output_redirection(t_cmnd  *node);
int		execute_commands_path(char *path_name, char **av, char **envp);
int		check_if_builtin(t_cmnd **node);

#endif
