#include "builtins.h"

int     update_oldpwd(t_env *env, char *oldpwd)
{
    char    cwd[10000];
    t_env   *tmp;
    char    *name;

    name = "OLDPWD";
    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, name) == 0)
        {
            tmp->value = oldpwd;
        }
        tmp = tmp->next;
    }
    return (SUCCESS);
}

char     *search_for_var(t_env *env, char  *search)
{
    t_env *tmp;
    char    *ret_path;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, search) == 0)
        {
            ret_path = tmp->value;
        }
        tmp = tmp->next;
    }
    return (ret_path);
}

int    home_case(t_env *env)
{
    char *home_path;
    char *home;
    char cwd[10000];

    home = "HOME";

    home_path = search_for_var(env, home);
    getcwd(cwd, sizeof(cwd));
    if (chdir(home_path) == 0)
    {
        update_oldpwd(env, cwd);
        ft_putstr_fd("Path changed successfully! in home_case\n", 1);
        return (SUCCESS);
    }
    else
    {
        ft_putstr_fd("cd: HOME not set", 1);
        ft_putstr_fd("Chdir failed in home_case\n", 1);
        return(ERROR);
    }
}

int    slash_case(t_env *env)
{
    char    *root_path;
    char    cwd[10000];

    getcwd(cwd, sizeof(cwd));
    if (chdir("/") == 0)
    {
        update_oldpwd(env, cwd);
        ft_putstr_fd("Path changed succesfully! in slash_case\n", 1);
        return (SUCCESS);
    }
    else
    {
        if (access("/", F_OK) == -1)
            ft_putstr_fd("no such file or directory: ", 1);
        else if (access("/", R_OK) == -1)
            ft_putstr_fd("permission denied: ", 1);
        ft_putstr_fd("Chdir failed in slash_case\n", 1);
        return(ERROR);
    }
}

int     absolute_path(t_env *env, char *absolute_path)
{
    char    cwd[10000];

    getcwd(cwd, sizeof(cwd));
    if (chdir(absolute_path) == 0)
    {
        update_oldpwd(env, cwd);
        ft_putstr_fd("Path changed succesfully! in absolute_path\n", 1);
        return (SUCCESS);
    }
    else
    {
        if (access(absolute_path, F_OK) == -1)
            ft_putstr_fd("No such file or directory: ", 1);
        else if (access(absolute_path, R_OK) == -1)
            ft_putstr_fd("permission denied: ",  1);
        ft_putstr_fd("Chdir failed in absolute_path\n", 1);
        return (ERROR);
    }
}

int    go_back(t_env   *env)
{
    char    cwd[10000];

    getcwd(cwd, sizeof(cwd));
    if (chdir("..") == 0)
    {
        update_oldpwd(env, cwd);
        ft_putstr_fd("Path changed succesfully! in go_back\n", 1);
        return (SUCCESS);
    }
    else
    {
        if (access("..", F_OK)  == -1)
            ft_putstr_fd("No such file or directory: ", 1);
        else if (access("..", R_OK) == -1)
            ft_putstr_fd("permission denied: ",  1);
        ft_putstr_fd("Chdir failed in go_back\n", 1);
        return (ERROR);
    }
}

int    do_whatever(t_env *env)
{
    char    cwd[10000];

    if (chdir(".") == 0)
    {
        ft_putstr_fd("Path not changed but it was a succes in do_whatever aka .", 1);
        return (SUCCESS);
    }
    else
    {
        if (access(".", F_OK) == -1)
            ft_putstr_fd("No such file or directory: ", 1);
        else if (access("..", R_OK) == -1)
            ft_putstr_fd("permission denied: ", 1);
        ft_putstr_fd("Chdir failed in do_whatever\n", 1);
        return (ERROR);
    }
}

void     cd(char **args, t_env *env)
{
    char    *s[] = {"ls", "-l", NULL};
    char    *a[] = {"pwd", NULL, NULL};

    if (!args[1] || args[1][0] == '~')
        home_case(env);
    else if (args[1][0] == '/' && args[1][1] == '\0')
        slash_case(env);
    else if (args[1])
        absolute_path(env, args[1]);
    else if (args[1][0] == '.' && args[1][1] == '.')
        go_back(env);
    else if (args[1][0] == '.')
        do_whatever(env);
    //execve("/bin/pwd", a, NULL);
    //execve("/bin/ls", s, NULL);
}
