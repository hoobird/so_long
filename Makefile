CC = cc -g
FLAGS = -Wall -Wextra -Werror
SRC = so_bindings.c  so_byebye.c  so_display2.c  so_display.c  so_floodfill.c  so_long.c  so_maphelper.c  so_mapvalidate.c  so_moving.c  so_setup.c  so_stringstuff.c  so_winning.c
OBJ = $(SRC:.c=.o)
FTPRINTF_PATH = ./ft_printf
LIBFT_PATH = $(FTPRINTF_PATH)/libft
FTPRINTF = $(FTPRINTF_PATH)/libftgnlprintf.a
MINILIBXPATH = ./minilibx-linux
MINILIBX = $(MINILIBXPATH)/libmlx_Linux.a
NAME = so_long

all: $(NAME)

$(NAME) : $(MINILIBX) $(FTPRINTF) $(OBJ)
	$(CC) $(FLAGS) -Imlx_linux $(OBJ) $(FTPRINTF) $(MINILIBX) -lXext -lX11 -lm -lz  -o $(NAME)

$(OBJ): $(SRC)
	$(CC) $(FLAGS) -c $(SRC)

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