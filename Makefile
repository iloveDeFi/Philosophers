# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bat <bat@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 10:28:15 by bat               #+#    #+#              #
#    Updated: 2023/07/18 11:34:58 by bat              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main.c \
        arg_parse.c \
        list.c \
        launch.c \
        threads.c \
        kill.c \
        utils.c

INCLUDES = philosophers.h \
           utils.h

INCLUDES_PATH = /philosophers/includes/

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

NAME = philo

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -O0

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -I${INCLUDES_PATH} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} $^ -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
