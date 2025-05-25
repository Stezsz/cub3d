# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/25 22:04:15 by tborges-          #+#    #+#              #
#    Updated: 2025/05/25 23:25:10 by tborges-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = cub3d
# LIBFT = libft/libft.a
# LIBFT_DIR = libft

# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# LFLAGS = -L./inc/mlx_mac -lmlx -LXext -lX11 - lm - lz
# RM = rm -f

# FILES = src/cub3d

# SRC = $(FILES:=.c)
# OBJ = $(FILES:=.o)
# HEADER = inc/cub3d.h
# INCLUDES = -I inc -I $(LIBFT_DIR)

# #Colors:
# GREEN		=	\033[92;5;118m
# YELLOW		=	\033[93;5;226m
# GRAY		=	\033[33;2;37m
# RESET		=	\033[0m
# CURSIVE		=	\033[33;3m

# .PHONY: all clean fclean re norm libft

# all: libft $(NAME)

# libft:
# 	@printf "$(CURSIVE)$(GRAY) 	- Making libft... $(RESET)\n"
# 	@$(MAKE) -C $(LIBFT_DIR)
# 	@printf "$(GREEN)    - Libft ready.\n$(RESET)"

# $(NAME): $(LIBFT) $(OBJ) $(HEADER)
# 	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
# 	@ $(CC) $(OBJ) $(INCLUDES) $(LDFLAGS) $(OPTS) $(LIBFT) -o $(NAME)
# 	@printf "$(GREEN)    - Executable ready.\n$(RESET)"

# $(LIBFT):
# 	@$(MAKE) -C $(LIBFT_DIR)

# %.o: %.c $(HEADER)
# 	@printf "$(CURSIVE)$(GRAY) 	- Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
# 	@ $(CC) $(CFLAGS) $(INCLUDES) $(OPTS) -c $< -o $@

# clean:
# 	@ $(RM) $(OBJ)
# 	@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
# 	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"
# 	@$(MAKE) -C $(LIBFT_DIR) clean

# norm:
# 	@printf "$(CURSIVE)$(GRAY)"
# 	@norminette
# 	@printf "$(RESET)"

# fclean: clean
# 	@ $(RM) $(NAME)
# 	@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
# 	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"
# 	@$(MAKE) -C $(LIBFT_DIR) fclean

# re: fclean all


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 10:04:55 by tborges-          #+#    #+#              #
#    Updated: 2025/05/25 22:48:21 by tborges-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nome do executável
NAME = cub3d

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./mlx -I ./libft -I /opt/X11/include

# Diretórios e arquivos
SRCS = src/cub3d.c
OBJS = $(SRCS:.c=.o)

# Diretório da libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Bibliotecas externas
MLX_FLAGS = -L ./mlx -L /opt/X11/lib -lmlx -lXext -lX11 -lm

# Regras
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all


# NAME = so_long

# SRC_DIR = src
# SRCS = so_long.c frees.c error.c map/map_init.c map/map_read.c \
# 		map/map_validation.c map/map_validation_aux.c render.c \
# 		input.c input_aux.c
# OBJS = $(SRCS:.c=.o)

# INCLUDES = -I/usr/include -Imlx -I$(LIBFT_DIR) -I$(MLX_DIR)

# LIBFT_DIR = ./libft
# LIBFT = ./libft/libft.a

# MLX_DIR = ./minilibx-linux
# MLX_LIB = $(MLX_DIR)/libmlx.a
# MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# RM = rm -rf

# all: $(NAME)

# $(NAME): $(OBJS)
# 	$(MAKE) -C $(LIBFT_DIR)
# 	$(MAKE) -C $(MLX_DIR)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_FLAGS)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# clean:
# 	$(MAKE) clean -C $(LIBFT_DIR)
# 	$(MAKE) clean -C $(MLX_DIR)
# 	$(RM) $(OBJS)

# fclean: clean
# 	$(MAKE) fclean -C $(LIBFT_DIR)
# 	$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
