#include "builtins.h"

t_env  *make_node(void)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    if (new == NULL)
        return (NULL);
    new->name = NULL;
    new->value = NULL;
	new->next = NULL;
    return (new);
}

t_list *ft_lstlast(t_list *lst)
{
    if (lst == NULL)
        return (NULL);
    while (lst->next != NULL)
    {
        lst = lst->next;
    }
    return (lst);
}

void    ft_lstadd_back(t_env *lst, t_env *new)
{
    while (lst != NULL)
    {
        lst = lst->next;
    }
    lst = new;
}

char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFFER_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char     *search_for_var(t_env *env, char  *search)
{
    t_env *tmp;
    char    *ret_path;

    tmp = env;
    while (tmp)
    {
        if (ft_strncmp(tmp->name, search, ft_strlen(tmp->name) + 1) == 0)
        {
            ret_path = tmp->value;
        }
        tmp = tmp->next;
    }
    return (ret_path);
}

t_env  *give_variable(t_env *env, char *search)
{
    t_env *tmp;
    
    tmp = env;
    while (tmp)
    {
        if (ft_strncmp(tmp->name, search, ft_strlen(tmp->name) + 1) == 0)
            return (tmp);
        tmp = tmp->next;
    }
    return(0);
}
