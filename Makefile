
NAME = parse.exec

PARSE_SRC = check_valid\
	handle_input\
	mini_input\
	mini_split\
	parsing_utils\
	split_pipes

#OBJ = check_valid\
	input_handle\
	mini_input\
	mini_split\
	parsing_utils\
	split_pipes

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(PARSE_SRC)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(PARSE_SRC)))

SRC_DIR = parse/

OBJ_DIR = parse/obj/

RLMAKE = readline/Makefile

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LDLIBS := -lreadline -lncurses

all: $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -I libft
	@mkdir -p parse/obj
	mv *.o parse/obj

$(NAME): $(OBJ)
	make -C libft
	make -C readline
	$(CC) $(CFLAGS) $(OBJ) readline/libhistory.a readline/libreadline.a libft/libft.a $(LDLIBS) -o $(NAME) -fsanitize=address -g3

clean:
	rm -fr $(OBJ_DIR)
	make clean -C libft
	make clean -C readline

fclean: clean
	make fclean -C libft
	rm -fr $(NAME)

re: fclean clean all