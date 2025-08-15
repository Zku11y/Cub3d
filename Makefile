NAME = cub3d

SRC = src/cub3d.c src/raycasting.c

OBJ = $(SRC:.c=.o)

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/mlx42lib/libmlx42.a
MLX_INC = -I$(MLX_DIR)
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

CC = cc
CFLAGS = -g -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC)
CFLAGS = -g -O1 -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC)
# CFLAGS = -g -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC) -fsanitize=address

# ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ./cub3d

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	cc $(CFLAGS) $(SRC) $(MLX_LIB) $(LIBFT_LIB) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
