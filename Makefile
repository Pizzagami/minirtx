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
		./srcs/tools.c			\
		./srcs/parsing.c		\
		./srcs/mlx_hook.c		\
		./srcs/pars2.c			\
		./srcs/tools2.c			\
		./srcs/tools3.c			\
		./srcs/tools4.c			\
		./srcs/tools4color.c	\
		./srcs/tools4vector.c	\
		./srcs/tools4vector2.c	\
		./srcs/tools4math.c		\
		./srcs/tools4lite.c		\
		./srcs/tools4aa.c		\
		./srcs/ft_split.c		\
		./srcs/tools4load.c		\
		./srcs/get_next_line.c	\
		./srcs/tools4dist.c		\


OBJS = ${SRCS:.c=.o}

CC  = gcc

FLAGS =   -L includes/minilibx -lmlx -framework OpenGL -framework Appkit -fsanitize=address -O0 -g3
CFLAGS =  -Wall -Wextra -Werror -I includes/ -I includes/minilibx
RM  = rm -f

${NAME}	:	${OBJS}
	@${CC}	 -o ${NAME}  ${FLAGS} ${OBJS}

all:  ${NAME}

clean:	
	${RM}	${OBJS}

fclean:  clean
	${RM} ${NAME}

re: fclean all
	${RM}	${OBJS} file.bmp

.PHONY: all clean fclean re