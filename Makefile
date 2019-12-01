# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by selgrabl          #+#    #+#              #
#    Updated: 2019/12/01 13:55:27 by selgrabl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirtx

SRCS = 	./srcs/minirtx.c	\
		./srcs/tools4math.c	\
		./srcs/tools4mlx.c	\
		./srcs/tools.c		\
		./srcs/parsing.c	\


OBJS = ${SRCS:.c=.o}

CC  = gcc

CFLAGS = -Iminilibx -Lminilibx -lmlx -framework OpenGL -framework Appkit -Wall -Wextra  -I./includes/

RM  = rm -f

${NAME}	:	${OBJS}
	${CC}	${CFLAGS} -o ${NAME} ${OBJS}

all:  ${NAME}

clean	:	
	${RM}	${OBJS}

fclean	:  clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re


















