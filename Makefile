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

SRCS = 	./srcs/display/anti_aliasing.c	\
		./srcs/others/basics.c			\
		./srcs/cals.c					\
		./srcs/display/color_basics.c	\
		./srcs/display/color.c			\
		./srcs/others/converters.c		\
		./srcs/display/dist_main.c		\
		./srcs/display/dist_others.c	\
		./srcs/display/filter.c			\
		./srcs/others/free.c			\
		./srcs/others/ft_split.c		\
		./srcs/others/get_next_line.c	\
		./srcs/hook.c					\
		./srcs/display/image.c			\
		./srcs/display/light.c			\
		./srcs/math/maths.c				\
		./srcs/math/matrix.c			\
		./srcs/minirtx.c				\
		./srcs/others/other_tools.c		\
		./srcs/others/other.c			\
		./srcs/parsing/pars_param.c		\
		./srcs/parsing/pars_annexe.c	\
		./srcs/parsing/pars1.c			\
		./srcs/parsing/pars2.c			\
		./srcs/parsing/pars3.c			\
		./srcs/parsing/parsing.c		\
		./srcs/others/put.c				\
		./srcs/others/readers.c			\
		./srcs/math/transformation.c	\
		./srcs/math/vector_basics.c		\
		./srcs/math/vector.c			\


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