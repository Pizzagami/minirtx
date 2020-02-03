# ************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by selgrabl          #+#    #+#              #
#    Updated: 2020/01/13 22:20:42 by selgrabl         ###   ########.fr        #
#                                                                              #
# ************************************************************************** #

NAME = miniRT

SRCS = 	./srcs/anti_aliasing.c	\
		./srcs/basics.c			\
		./srcs/cals.c			\
		./srcs/color_basics.c	\
		./srcs/color.c			\
		./srcs/converters.c		\
		./srcs/dist_main.c		\
		./srcs/dist_others.c	\
		./srcs/filter.c			\
		./srcs/free.c			\
		./srcs/ft_split.c		\
		./srcs/get_next_line.c	\
		./srcs/hook.c			\
		./srcs/image.c			\
		./srcs/light.c			\
		./srcs/maths.c			\
		./srcs/matrix.c			\
		./srcs/minirtx.c		\
		./srcs/other_tools.c	\
		./srcs/other.c			\
		./srcs/pars2.c			\
		./srcs/parsing.c		\
		./srcs/put.c			\
		./srcs/readers.c		\
		./srcs/transformation.c	\
		./srcs/vector_basics.c	\
		./srcs/vector.c			\


OBJS = ${SRCS:.c=.o}

CC  = gcc

FLAGS =   -L includes/minilibx -lmlx -framework OpenGL -framework Appkit -O0 -g3
CFLAGS =  -Wall -Wextra -Werror -I includes/ -I includes/minilibx

${NAME}	:	${OBJS}
	${CC}	 -o ${NAME}  ${FLAGS} ${OBJS}

all:  ${NAME}

clean:	
	${RM}	${OBJS}

fclean:  clean
	${RM} ${NAME}

re: fclean all
	${RM}	${OBJS} file.bmp

.PHONY: all clean fclean re