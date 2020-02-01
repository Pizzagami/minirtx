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

SRCS = 	./srcs/minirtx.c		\
		./srcs/anti_aliasing.c	\
		./srcs/basics.c			\
		./srcs/cals.c			\
		./srcs/color.c			\
		./srcs/color_basics.c	\
		./srcs/converters.c		\
		./srcs/filter.c			\
		./srcs/image.c			\
		./srcs/parsing.c		\
		./srcs/put.c			\
		./srcs/readers.c		\
		./srcs/hook.c			\
		./srcs/pars2.c			\
		./srcs/other_tools.c	\
		./srcs/tools4vector.c	\
		./srcs/tools4vector2.c	\
		./srcs/transformation.c	\
		./srcs/tools4math.c		\
		./srcs/light.c		\
		./srcs/ft_split.c		\
		./srcs/tools4load.c		\
		./srcs/get_next_line.c	\
		./srcs/tools4dist.c		\
		./srcs/solver.c			\


OBJS = ${SRCS:.c=.o}

CC  = gcc

FLAGS =   -L includes/minilibx -lmlx -framework OpenGL -framework Appkit -fsanitize=address -O0 -g3
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