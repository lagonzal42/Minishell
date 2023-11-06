

NAME = minishell

OBJ_DIR = obj/

############################### REDIRECTION ######################################
REDIRECTION = add_cmd\
	node_create\
	print_commands_utils\
	quoute_trim\
	redirection_utils\
	redirection

REDIRECTION_SRC_DIR = redirection/
REDIRECTION_SRC = $(addprefix $(REDIRECTION_SRC_DIR), $(addsuffix .c, $(REDIRECTION)))
REDIRECTION_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(REDIRECTION)))
############################### EXECUTION ######################################
EXECUTION = execution_utils\
	find_path\
	path_utils\
	pipe_hell

EXECUTION_SRC_DIR = execution/
EXECUTION_SRC = $(addprefix $(EXECUTION_SRC_DIR), $(addsuffix .c, $(EXECUTION)))
EXECUTION_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(EXECUTION)))
############################### PARSE ######################################
PARSE = check_valid\
	handle_input\
	mini_input\
	mini_split\
	parsing_utils\
	split_pipes\
	signals

PARSE_SRC_DIR = parse/
PARSE_SRC = $(addprefix $(PARSE_SRC_DIR), $(addsuffix .c, $(PARSE)))
PARSE_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(PARSE)))

############################### EXPAND ####################################

EXPAND = expand\
	expand_utils

EXPAND_SRC_DIR = expand/
EXPAND_SRC = $(addprefix $(EXPAND_SRC_DIR), $(addsuffix .c, $(EXPAND)))
EXPAND_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(EXPAND)))

############################## BUILTIN ####################################

BUILTINS = cd\
	cd1\
	echo\
	env\
	export\
	pwd\
	utils_export\
	utils_export1\
	utils_unset\
	utils_env\
	utils1\
	unset\
	exit

BULITINS_SRC_DIR = builtins/
BUILTINS_SRC = $(addprefix $(BULITINS_SRC_DIR), $(addsuffix .c, $(BUILTINS)))
BUILTINS_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BUILTINS)))

#########################################################################

OBJ = $(PARSE_OBJ) \
	$(BUILTINS_OBJ)\
	$(EXPAND_OBJ) \
	$(EXECUTION_OBJ)\
	$(REDIRECTION_OBJ)

# OBJ := $(SRC:%.c=%.o)

SRC = $(BUILTINS_SRC) $(EXPAND_SRC) $(PARSE_SRC) $(EXECUTION_SRC) $(REDIRECTION_SRC) 

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LDLIBS := -lreadline -lncurses

#val:$(NAME)
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./minishell

all: $(NAME)

$(CONFIG):
		bash ./configure.sh


$(OBJ): $(SRC)
	/bin/echo -n "Compiling minishell objs."
	$(CC) $(CFLAGS) -c $(SRC) -I libft
	@mkdir -p $(OBJ_DIR)
	mv *.o $(OBJ_DIR)
	/bin/echo ".."

$(NAME): $(OBJ) $(RLMAKE) $(CONFIG)
	/bin/echo -n "Compiling libft."
	make -C libft
	/bin/echo ".."
	/bin/echo -n "Configuring readline."
	bash ./configure.sh > /dev/null 2>&1
	/bin/echo ".."
	/bin/echo -n "Compiling readline."
	make -C readline >/dev/null 2>&1
	/bin/echo ".."
	/bin/echo -n "Compiling minishell."
	$(CC) $(CFLAGS) $(OBJ) readline/libhistory.a readline/libreadline.a libft/libft.a  -I ./realdine -L./readline $(LDLIBS) -o $(NAME) 
	/bin/echo ".."
	/bin/echo "Minishell compiled!"

clean:
	/bin/echo -n "Cleaning objects."
	rm -fr $(OBJ_DIR)
	make clean -C libft
	make clean -C readline
	/bin/echo ".."
	/bin/echo "Cleaning completed!"


fclean: clean
	make fclean -C libft
	/bin/echo -n "Full cleaning."
	@rm -fr $(NAME) expand/expand.h.gch builtins.h.gch builtins/builtins.h.gch redirection/redirection.h.gch execution/execution.h.gch parse/parse.h.gch minishell.dSYM
	/bin/echo ".."
	/bin/echo "Full cleaning completed!"

re: fclean clean all
	/bin/echo  "Project completely recompiled!"

norm:
	norminette $(SRC) builtins/builtins.h execution/execution.h expand/expand.h redirection/redirection.h parse/parse.h