NAME = cub3d

SRC = src/cub3d.c src/raycasting.c

OBJ = $(SRC:.c=.o)

MLX_DIR = includes
MLX_LIB = ./lib/libmlx42.a
MLX_INC = -I$(MLX_DIR)

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

CUB3D_HEADER = includes/cub3d.h

CC = cc

CFLAGS = -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC) \
         -I/Users/mdakni/.brew/opt/glfw/include 

LDFLAGS = -L"/Users/mdakni/.brew/opt/glfw/lib" -lglfw \
          -framework Cocoa -framework OpenGL -framework IOKit \
		-fsanitize=address -g3 -O3

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

%.o: %.c $(CUB3D_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)