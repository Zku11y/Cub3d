NAME = cub3D

SRC = ./render_ing/cub3D.c \
	./render_ing/ft_raycasting/raycasting.c \
	./render_ing/ft_raycasting/raycasting2.c \
	./render_ing/ft_raycasting/raycasting3.c \
	./pars_ing/ts_data/ts_teto.c \
	./pars_ing/ts_check/rec_map.c\
	./pars_ing/ts_check/dot_chk.c \
	./pars_ing/ts_check/ts_check_data.c \
	./pars_ing/ts_data/ts_key.c \
	./pars_ing/ts_data/ts_opn.c \
	./pars_ing/ts_data/ts_put.c \
	./pars_ing/ts_data/ts_rgb.c \
	./pars_ing/ts_data/ts_val.c \
	./pars_ing/ts_data/ts_read.c \
	./pars_ing/ts_data/ts_read_map.c \
	./pars_ing/ts_data/free_nu_map.c \
	./pars_ing/ts_pars.c \
	./render_ing/ft_init/ft_init_0.c \
	./render_ing/ft_init/ft_init_1.c \
	./render_ing/ft_init/ft_init_2.c \
	./render_ing/ft_init/ft_init_3.c \
	./render_ing/ft_init/ft_update_buff_init.c \
	./render_ing/ft_init/ft_update_res_init.c \
	./render_ing/ft_init/ft_map_init.c \
	./render_ing/ft_utils/ft_lerp.c \
	./render_ing/ft_utils/ft_utils.c \
	./render_ing/ft_utils/ft_utils2.c \
	./render_ing/ft_utils/ft_utils3.c \
	./render_ing/ft_player/ft_heart.c \
	./render_ing/ft_player/ft_health.c \
	./render_ing/ft_player/ft_mouvement.c \
	./render_ing/ft_player/ft_mouvement2.c \
	./render_ing/ft_render/ft_tilt.c \
	./render_ing/ft_render/ft_render.c \
	./render_ing/ft_render/ft_render2.c \
	./render_ing/ft_render/ft_render3.c \
	./render_ing/ft_render/ft_floor_ceiling.c \
	./render_ing/ft_clean/ft_clean.c


OBJ = $(SRC:.c=.o)

MLX_DIR = includes
MLX_INC = -I$(MLX_DIR)

LIBTS_DIR = ./pars_ing/libts
LIBTS_INC = -I$(LIBTS_DIR)

CUB3D_HEADER = includes/cub3d.h

CC = cc

FT_UNAME := $(shell uname -s)

CFLAGS = -O3 -Wall -Wextra -Werror $(MLX_INC) $(LIBTS_INC)

	MLX_LIB = ../MLX42/build/libmlx42.a
	LIBTS_LIB = ./lib/libts_mac.a
	LDFLAGS = -L"/goinfre/mdakni/homebrew/Cellar/glfw/3.4/lib" -lglfw \
          -framework Cocoa -framework OpenGL -framework IOKit 

$(NAME): $(OBJ) $(MLX_LIB) $(LIBTS_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LIBTS_LIB) $(LDFLAGS) -o $(NAME)

$(LIBTS_LIB):
	make -C $(LIBTS_DIR)

$(OBJ): $(CUB3D_HEADER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)