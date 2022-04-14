# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/15 15:04:29 by tamigore          #+#    #+#              #
#    Updated: 2022/04/14 16:37:38 by tamigore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

INC = libmath.h

DIR_I = includes

DIR_S = srcs

DIR_O = objs

SRC =	vector.c	\
		vector_2.c	\
		angles.c	\
		matrix.c	\
		matrix_op.c	\
		matrix_tr.c

SRCS = $(addprefix $(DIR_S)/,$(SRC))

OBJ = $(SRC:.c=.o)

OBJS = $(addprefix $(DIR_O)/,$(OBJ))

FLAGS = -Wall -Werror -Wextra -I $(DIR_I)

NAME = libmath.a

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJS) : $(SRCS) $(DIR_I)/$(INC)
	mkdir -p $(DIR_O)
	$(CC) $(FLAGS) -c $(SRCS)
	mv $(OBJ) $(DIR_O)

clean :
	rm -rf $(DIR_O)

fclean : clean
	rm -rf $(NAME)

re : fclean all
