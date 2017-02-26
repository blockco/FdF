NAME = fdf

CC = gcc -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror

SRC = gnl/get_next_line.c src/*.c

FRAMEWORKS = -framework OpenGL -framework Appkit

INCLUDE = -I includes

INCLUDE_MLX = -I mlx
LINK_MLX = -L mlx -lmlx
MLX = $(INCLUDE_MLX) $(LINK_MLX)

INCLUDE_LIBFT = -I libft/includes
LINK_LIBFT = -L libft/ -lft
LIBFT = $(INCLUDE_LIBFT) $(LINK_LIBFT)

GNL = -I gnl

all: $(NAME)

libft.a:
	make -C libft

mlx.a:
	make -C mlx

$(NAME): libft.a mlx.a
	$(CC) $(MLX) $(LIBFT) $(GNL) $(INCLUDE) $(FRAMEWORKS) $(SRC) -o $(NAME)

clean:
	make -C libft fclean
	make -C mlx clean

fclean: clean
	rm -rf $(NAME)

re: clean all
