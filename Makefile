NAME 			= pipex

CC 				= cc
RM				= rm -f
CLONE 			= git clone --depth=1

CFLAGS 			= -Wall -Wextra -Werror -ggdb

LIB_C_GIT_URL 	= git@github.com:MiniKlar/LIB_C.git
LIB_C			= LIB_C

SRC 			= ./main.c \

OBJ 			= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIB_C) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ./LIB_C/LIB_C.a -o $(NAME)

$(LIB_C):
	git clone $(LIB_C_GIT_URL) $(LIB_C)
	$(MAKE) -C $(LIB_C)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(LIB_C)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

clear: fclean
	$(RM) -rf $(MLX)

re: fclean all

.PHONY:	all bonus clear clean fclean re
