# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 20:00:22 by ksudyn            #+#    #+#              #
#    Updated: 2025/07/01 18:23:55 by ksudyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
INC_DIR = ./includes

SRCS =	src/dimensions.c\
		src/error.c\
		src/flood_fill.c\
		src/main.c\
		src/parse.c\
		src/utils_parse.c\
		src/validate_map.c\
	

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes -I./libft -I./minilibx-linux

LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
