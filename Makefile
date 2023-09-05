
NAME = parse.exec

OBJ_DIR = obj/

############################### PARSE ######################################
PARSE = check_valid\
	handle_input\
	mini_input\
	mini_split\
	parsing_utils\
	split_pipes

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
	echo\
	env\
	export\
	pwd\
	utils_export\
	utils_unset\
	utils1

BULITINS_SRC_DIR = builtins/
BUILTINS_SRC = $(addprefix $(BULITINS_SRC_DIR), $(addsuffix .c, $(BUILTINS)))
BUILTINS_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(BUILTINS)))

#########################################################################

OBJ = $(PARSE_OBJ) \
	$(BUILTINS_OBJ)\
	$(EXPAND_OBJ)
SRC = $(BUILTINS_SRC) $(EXPAND_SRC) $(PARSE_SRC)

RLMAKE = readline/Makefile

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LDLIBS := -lreadline -lncurses

all: $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -I libft
	@mkdir -p $(OBJ_DIR)
	mv *.o $(OBJ_DIR)

$(NAME): $(OBJ) $(RLMAKE)
	make -C libft
	@make -C readline
	$(CC) $(CFLAGS) $(OBJ) readline/libhistory.a readline/libreadline.a libft/libft.a  -I realdine $(LDLIBS) -o $(NAME) -fsanitize=address -g3

clean:
	rm -fr $(OBJ_DIR)
	make clean -C libft
	make clean -C readline

fclean: clean
	make fclean -C libft
	rm -fr $(NAME)

re: fclean clean all

norm:
	norminette $(SRC)