# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bat <bat@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 10:28:15 by bat               #+#    #+#              #
#    Updated: 2023/07/11 17:29:34 by bat              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES		= 	main \
				arg_parse \
				list \
				launch \
				threads \
				kill \
			  	utils

SRCS	= $(wildcard *.c)

OBJS	= $(SRCS:%.c=%.o)

NAME	= philo

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address
# TFLAGS	= -lpthread -fsanitize=thread

all:		${NAME}

%.o:	%.c
		${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
		${CC} ${CFLAGS} $^ -o $@

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all bonus clean fclean re