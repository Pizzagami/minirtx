# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by selgrabl          #+#    #+#              #
#    Updated: 2019/12/11 14:23:20 by braimbau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = 	./srcs/minirtx.c		\
		./srcs/tools.c			\
		./srcs/parsing.c		\
		./srcs/mlx_hook.c		\
		./srcs/pars2.c			\
		./srcs/tools2.c			\
		./srcs/tools3.c			\
		./srcs/tools4color.c	\
		./srcs/tools4vector.c	\
		./srcs/tools4vector2.c	\
		./srcs/tools4math.c		\
		./srcs/ft_split.c		\
		./srcs/get_next_line.c	\


OBJS = ${SRCS:.c=.o}

CC  = gcc

CFLAGS =  -fsanitize=address -g3 -Lincludes/minilibx -lmlx -framework OpenGL -framework Appkit -Wall -Wextra -I./includes/

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


















