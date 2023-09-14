#include "builtins.h"

void    print_env(t_env *env, char **standardized)
{
    t_env   *tmp;
    
    tmp = env;
    if (*standardized != NULL)
    {
        ft_putstr_fd("env: ", STDERR_FILENO);
        ft_putstr_fd(*standardized, STDERR_FILENO);
        ft_putstr_fd(": No such file or directory", STDERR_FILENO);
    }
    while(tmp != NULL)
    {
        ft_printf("%s=%s\n", tmp->name, tmp->value);
        tmp = tmp->next;
    }
}
