# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by selgrabl          #+#    #+#              #
#    Updated: 2019/12/04 19:08:45 by selgrabl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = 	./srcs/minirtx.c	\
		./srcs/tools4math.c	\
		./srcs/tools.c		\
		./srcs/parsing.c	\
		./srcs/pars2.c		\
		./srcs/tools2.c		\
		./srcs/mlx_hook.c	\


OBJS = ${SRCS:.c=.o}

CC  = gcc

CFLAGS =  -Lincludes/minilibx -lmlx -framework OpenGL -framework Appkit -Wall -Wextra  -I./includes/

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


















