# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by selgrabl          #+#    #+#              #
#    Updated: 2019/11/30 15:53:20 by selgrabl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirtx

SRCS = 	./main.c		\
		./tools4math.c	\
		./tools4mlx.c	\
		./tools.c		\
		./parsing.c		\


OBJS = ${SRCS:.c=.o}

CC  = gcc

CFLAGS = -Iminilibx -Lminilibx -lmlx -framework OpenGL -framework Appkit -Wall -Wextra  -I./

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


















