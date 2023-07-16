# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bat <bat@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 10:28:15 by bat               #+#    #+#              #
#    Updated: 2023/07/16 12:06:16 by bat              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES		= 	main \
				arg_parse \
				list \
				launch \
				threads \
				kill \
			  	utils

INCLUDES	= philosophers.h \
				utils.h

PATH	= ./includes/

LIB_PATH	= ./libft/

LIBFT 	= ${LIB_PATH}libft.a

HEADERS = $(addprefix $(PATH), $(INCLUDES))

SRCS	= $(wildcard src/*.c)

OBJS	= $(SRCS:%.c=%.o)

NAME	= philo

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address
# TFLAGS	= -lpthread -fsanitize=thread

all:		${LIBFT} ${NAME}

${LIBFT}: ${LIB_PATH} 
	make -C ${LIB_PATH}


%.o:	%.c
		${CC} ${CFLAGS} -I${PATH} -c $< -o $@ 

${NAME}:	${OBJS}
		${CC} ${CFLAGS} $^ -o $@

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all bonus clean fclean re