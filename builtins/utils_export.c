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

t_env *ft_lstlast(t_env *lst)
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
    while (lst->next)
    {
        lst = lst->next;
    }
    lst->next = new;
}

t_env	*ft_lstnew(char	*name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
    new->value = value;
    new->next = NULL;
	return (new);
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

    ret_path = NULL;
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

int give_variable(t_env *env, t_env **ret, char *search)
{  
    *ret = env;

    while ((*ret)->next != NULL)
    {
        if (ft_strcmp((*ret)->name, search) == 0)
            return (0);
        *ret = (*ret)->next;
    }
    return(1);
}
