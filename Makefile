# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: braimbau <braimbau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by selgrabl          #+#    #+#              #
#    Updated: 2020/01/10 10:38:13 by braimbau         ###   ########.fr        #
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
		./srcs/tools4.c			\
		./srcs/tools4color.c	\
		./srcs/tools4vector.c	\
		./srcs/tools4vector2.c	\
		./srcs/tools4math.c		\
		./srcs/tools4lite.c		\
		./srcs/tools4aa.c		\
		./srcs/ft_split.c		\
		./srcs/get_next_line.c	\
		./srcs/tools4dist.c		\


OBJS = ${SRCS:.c=.o}

CC  = gcc

FLAGS =   -L includes/minilibx -lmlx -framework OpenGL -framework Appkit -fsanitize=address -g3
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
	${RM}	${OBJS}

.PHONY: all clean fclean re


















