# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/19 16:16:11 by tamigore          #+#    #+#              #
#    Updated: 2021/01/08 11:46:12 by tamigore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

LIB = lib/

LIBFT = $(LIB)libft

LIBMATH = $(LIB)libmath

DIR_S = srcs/

HEADER = includes/

SOURCES =	miniRT.c	\
			parsing.c	\
			conv_nb.c	\
			utils.c		\
			mlx.c		\
			matrix.c	\
			intersect.c \
			obj.c		\
			trace.c		\
			ray.c		\
			print.c		\
			count.c

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I $(HEADER) -D NUM_THREADS=$(NUM_THREADS)

FLAGS = -L $(LIBFT) -lft -L $(LIBMATH) -lmath

MACOS_MACRO = -D MACOS

LINUX_MACRO = -D LINUX

MACOS_FLAGS = -L $(LIB)minilibx_opengl_20191021 -lmlx -framework Appkit -framework OpenGL

LINUX_FLAGS = -L $(LIB)minilibx-linux -lmlx -lm -lX11 -lXext -lpthread

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	NUM_THREADS = $(shell sysctl -n hw.ncpu)
	CFLAGS += $(MACOS_MACRO)
	FLAGS += $(MACOS_FLAGS)
endif
ifeq ($(UNAME),Linux)
	NUM_THREADS = $(shell nproc --all)
	CFLAGS += $(LINUX_MACRO)
	FLAGS += $(LINUX_FLAGS)
endif

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	make -C $(LIBFT)
	make -C $(LIBMATH)
	gcc -g $(CFLAGS) $(OBJS) $(FLAGS) -o $(NAME)

norme:
	norminette ./$(LIB)
	@echo
	norminette ./$(HEADER)
	@echo
	norminette ./$(DIR_S)

bonus: all

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT)
	@make clean -C $(LIBMATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(LIBMATH)

re: fclean all
