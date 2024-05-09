CC = cc -g
FLAGS = -Wall -Wextra -Werror
SRC = so_long.c
OBJ = $(SRC:.c=.o)
FTPRINTF_PATH = ./ft_printf
LIBFT_PATH = $(FTPRINTF_PATH)/libft
FTPRINTF = $(FTPRINTF_PATH)/libftgnlprintf.a
NAME = prog

all: $(NAME)

$(NAME): $(OBJ) $(FTPRINTF)
	$(CC) $(OBJ) $(FTPRINTF) minilibx-linux/libmlx_Linux.a minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm -lz -o $(NAME)


$(OBJ): $(SRC)
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(FTPRINTF):
	make -C $(FTPRINTF_PATH) all

clean:
	rm -f $(OBJ)
	make -C $(FTPRINTF_PATH) clean

fclean: clean
	rm -f $(OBJ) $(NAME)
	make -C $(FTPRINTF_PATH) fclean

re:	fclean all

phony: all fclean clean re libft ft_printf so_long