#ifndef	BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define	ERROR 1
# define	SUCCESS 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

				//BUILTIN FUNCTIONS:
void     cd(char **args, t_env *env);
int		echo(char **args);
void	pwd(char **cmd);
void	export(t_env *env, char **args);

				//FUNCTIONS:
t_env	*get_env(char **envp, t_env *env);
char	*get_env_name(char *dest, const char *src);
t_env  	*make_node(void);
void    print_nodes(t_env   *env);
t_env 	*ft_lstlast(t_env *lst);
void    ft_lstadd_back(t_env *lst, t_env *new);
int		ft_strcmp(char *s1, char *s2);
char    *search_for_var(t_env *env, char *search);
int    	home_case(t_env *env);
int    	slash_case(t_env *env);
int    	go_back(t_env   *env);
int     absolute_path(t_env *env, char *absolute_path);
int    	do_whatever(void);
int		check_var_name(char	arg);
int		give_variable(t_env *env, t_env **tmp, char *search);
t_env	*ft_lstnew(char	*name, char *value);
char	*return_env_value(char **args);

				//EXPORT:
char	*check_env_string(char **args);

#endif
