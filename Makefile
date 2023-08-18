
PARSE_SRC = check_valid.c\
	input_handle.c\
	mini_input.c\
	mini_split.c\
	parsing_utils.c\
	split_pipes.c

OBJ = check_valid.o\
	input_handle.o\
	mini_input.o\
	mini_split.o\
	parsing_utils.o\
	split_pipes.o


OBJ_DIR = parse/obj

RLMAKE = readline/Makefile

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LDLIBS := -lreadline -lncurses

$(RLMAKE) :
	cd ./readline;\
		./configure;\
	cd ..

%.o:%.c
	@$(CC) $(CFLAGS) -c $(PARSE_SRC)


all: $(OBJ) $(RLMAKE) 
	make -C readline
	$(CC) $(CFLAGS) $(OBJ) readline/libhistory.a readline/libreadline.a libft/libft.a $(LDLIBS) -o parse.exec

