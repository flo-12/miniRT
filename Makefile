# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbecht <fbecht@student.42berlin.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 15:51:49 by fbecht            #+#    #+#              #
#    Updated: 2023/08/01 15:51:51 by fbecht           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME	= miniRT

# Compiler
CC		= cc
CFLAGS	= -Werror -Wextra -Wall

# Libft
LIBFT_PATH	= Libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# MiniLibX
MINILIBX = libmlx_Linux.a
MINILIBX_PATH = ./minilibx_linux/
MLX	= $(MINILIBX_PATH)$(MINILIBX)

# includes
INC			=	-I ./includes/ \
				-I ./$(LIBFT_PATH) \
				-I ./$(MINILIBX_PATH)

# Sources
SRC_PATH	=	srcs/
SRC			=	main.c \
				parser.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Compiling
all: $(LIBFT) $(MLX) $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@-$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC)
	@echo "\n\t\033[33;1;3m$(NAME) ready\033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
#	@echo "Compiling object files"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@echo "Generating obj folders..."
	@mkdir $(OBJ_PATH)

$(MLX):
	@echo "Making MiniLibX..."
	@make -sC $(MINILIBX_PATH)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)
	@make clean -sC $(LIBFT_PATH)

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@echo "Removing minishell..."
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)

re: fclean all

norminette_check:
	norminette ./src
	norminette -R CheckForbiddenSourceHeader ./includes

.PHONY: all re clean fclean norminette_check compile_mac
