# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tamigore <tamigore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/19 16:16:11 by tamigore          #+#    #+#              #
#    Updated: 2020/03/11 17:56:50 by tamigore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = miniRT

FLAGS = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -L libft -lft -O3

LIBFT = libft

DIR_S = srcs

DIR_O = objs

HEADER = includes

SOURCES = miniRT.c	\
		  parsing.c	\
		  conv_nb.c	\
		  mlx.c		\
		  utils.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(FLAGS) -I $(HEADER) $(OBJS) -o $@

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/miniRT.h
	mkdir -p objs
	$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	norminette ./libft/
	@echo
	norminette ./$(HEADER)/
	@echo
	norminette ./$(DIR_S)/

bonus: all

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
