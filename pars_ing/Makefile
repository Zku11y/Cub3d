# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 17:56:59 by oel-mado          #+#    #+#              #
#    Updated: 2026/03/08 20:02:14 by oel-mado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub-tst

# CFLAGS = -Wall -Werror -Wextra
CFLAGS = -fsanitize=address -g

OBJ = ${SRC:.c=.o}
CC = cc

LIBTS_D = libts
LIBTS_A = $(LIBTS_D)/libts.a

FILE = ../test/test.cub ../test/crazy.cub
SRC = ts_data/ts_teto.c \
	ts_check/rec_map.c\
	ts_check/dot_chk.c \
	ts_check/map_cln.c \
	ts_check/ts_check_data.c \
	ts_check/ts_check_elv.c \
	ts_data/free_nu_map.c \
	ts_data/ts_key.c \
	ts_data/ts_opn.c \
	ts_data/ts_put.c \
	ts_data/ts_val.c \
	ts_data/ts_read.c \
	ts_data/ts_read_map.c \
	ts_pars.c \
	main.c \
	\

m: all clean

t: m
	./$(NAME) $(FILE)

all: $(LIBTS_A) $(NAME)

$(LIBTS_A):
	make re -C $(LIBTS_D)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBTS_A) -o $(NAME)

%.o: %.c head.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

c: clean

fclean: clean
	rm -f $(NAME)

f: fclean

re: fclean all

.PHONY: clean
