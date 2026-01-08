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

FT_UNAME := $(shell uname -s)

# Linux Compilation

# CFLAGS = -g -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC)
# CFLAGS = -g -O3 $(MLX_INC) $(LIBFT_INC)
# CFLAGS = -g -O1 -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC)
# LDFLAGS = -ldl -lglfw -pthread -lm

# $(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
# 	cc $(CFLAGS) $(SRC) $(MLX_LIB) $(LIBFT_LIB) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

# MacOS Compilation :

# CFLAGS = -g -O3 -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC) \
#          -I/Users/mdakni/.brew/opt/glfw/include 
CFLAGS = -g -O3 -Wall -Wextra -Werror $(MLX_INC) $(LIBFT_INC)

ifeq ($(FT_UNAME), Darwin)

	LDFLAGS = -L"/Users/mdakni/.brew/opt/glfw/lib" -lglfw \
          -framework Cocoa -framework OpenGL -framework IOKit -fsanitize=address -g
# LDFLAGS = -lglfw -framework Cocoa -framework OpenGL -framework IOKit \
# 		-fsanitize=address -g

endif

ifeq ($(FT_UNAME), Linux)

	LDFLAGS = -ldl -lglfw -pthread -lm

endif

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