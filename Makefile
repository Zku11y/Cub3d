NAME = cub3d

SRC = src/cub3d.c

OBJ = $(SRC:.c=.o)

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/mlx42lib/libmlx42.a
MLX_INC = -I$(MLX_DIR)
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

CC = cc
CFLAGS = -g -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC)
# CFLAGS = -g -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC) -fsanitize=address

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
