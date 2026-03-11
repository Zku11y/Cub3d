# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 17:00:38 by oel-mado          #+#    #+#              #
#    Updated: 2026/02/27 17:02:46 by oel-mado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libts.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ts_atoi.c\
	ts_bzero.c\
	ts_calloc.c\
	ts_isalnum.c\
	ts_isalpha.c\
	ts_isascii.c\
	ts_isdigit.c\
	ts_isprint.c\
	ts_itoa.c\
	ts_memchr.c\
	ts_memcmp.c\
	ts_memcpy.c\
	ts_memmove.c\
	ts_memset.c\
	ts_putchar_fd.c\
	ts_putendl_fd.c\
	ts_putnbr_fd.c\
	ts_putstr_fd.c\
	ts_split.c\
	ts_strchr.c\
	ts_strdup.c\
	ts_strndup.c\
	ts_striteri.c\
	ts_strjoin.c\
	ts_strlcat.c\
	ts_strlcpy.c\
	ts_strlen.c\
	ts_strmapi.c\
	ts_strncmp.c\
	ts_strnstr.c\
	ts_strrchr.c\
	ts_strtrim.c\
	ts_substr.c\
	ts_tolower.c\
	ts_toupper.c \
	ts_lstnew_bonus.c\
	ts_lstadd_front_bonus.c\
	ts_lstadd_back_bonus.c\
	ts_lstsize_bonus.c\
	ts_lstlast_bonus.c\
	ts_lstdelone_bonus.c\
	ts_lstclear_bonus.c\
	ts_lstiter_bonus.c\
	ts_lstmap_bonus.c\
	gnl.c gnlu.c\

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	ar rcs ${NAME} ${OBJ}

%.o: %.c libts.h
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
