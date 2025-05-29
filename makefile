# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/25 22:04:15 by tborges-          #+#    #+#              #
#    Updated: 2025/05/27 19:21:34 by tborges-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
LIBFT = libft/libft.a
LIBFT_DIR = libft

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L./inc/mlx_mac -lmlx -LXext -lX11 - lm - lz
RM = rm -f

FILES = src/cub3d src/player

SRC = $(FILES:=.c)
OBJ = $(FILES:=.o)
HEADER = includes/cub3d.h
INCLUDES = -I inc -I $(LIBFT_DIR)

#Colors:
GREEN		=	\033[92;5;118m
YELLOW		=	\033[93;5;226m
GRAY		=	\033[33;2;37m
RESET		=	\033[0m
CURSIVE		=	\033[33;3m

.PHONY: all clean fclean re norm libft

all: libft $(NAME)

libft:
	@printf "$(CURSIVE)$(GRAY) 	- Making libft... $(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(GREEN)    - Libft ready.\n$(RESET)"

$(NAME): $(LIBFT) $(OBJ) $(HEADER)
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	@ $(CC) $(OBJ) $(INCLUDES) $(LDFLAGS) $(OPTS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)    - Executable ready.\n$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	@printf "$(CURSIVE)$(GRAY) 	- Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
	@ $(CC) $(CFLAGS) $(INCLUDES) $(OPTS) -c $< -o $@

clean:
	@ $(RM) $(OBJ)
	@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) clean

norm:
	@printf "$(CURSIVE)$(GRAY)"
	@norminette
	@printf "$(RESET)"

fclean: clean
	@ $(RM) $(NAME)
	@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

re: fclean all

.PHONY: all clean fclean re
