CC = cc -g
FLAGS = -Wall -Wextra -Werror
SRC = so_long.c
OBJ = $(SRC:.c=.o)
FTPRINTF_PATH = ./ft_printf
LIBFT_PATH = $(FTPRINTF_PATH)/libft
FTPRINTF = $(FTPRINTF_PATH)/libftgnlprintf.a
MINILIBXPATH = ./minilibx-linux
MINILIBX = $(MINILIBXPATH)/libmlx_Linux.a
NAME = prog

all: $(NAME)

$(NAME): $(OBJ) $(FTPRINTF) $(MINILIBX)
	$(CC) $(OBJ) $(FTPRINTF) $(MINILIBX) -lXext -lX11 -lm -lz -o $(NAME)


$(OBJ): $(SRC)
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(FTPRINTF):
	make -C $(FTPRINTF_PATH) all

$(MINILIBX):
	make -C $(MINILIBXPATH) all

clean:
	rm -f $(OBJ)
	make -C $(FTPRINTF_PATH) clean
	make -C $(MINILIBXPATH) clean

fclean: clean
	rm -f $(OBJ) $(NAME)
	make -C $(FTPRINTF_PATH) fclean
	make -C $(MINILIBXPATH) clean

re:	fclean all

phony: all fclean clean re libft ft_printf so_long