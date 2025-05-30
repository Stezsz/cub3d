# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tborges- <tborges-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/25 22:04:15 by tborges-          #+#    #+#              #
#    Updated: 2025/05/30 23:42:07 by tborges-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_DIR = src
OBJDIR = obj
INC_DIR = includes

LIBFT = $(INC_DIR)/libft/libft.a
LIBFT_DIR = $(INC_DIR)/libft

MLX = $(INC_DIR)/mlx/libmlx.a
MLX_DIR = $(INC_DIR)/mlx

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./$(INC_DIR)/mlx -lmlx -lXext -lX11 -lm -lz
RM = rm -f

FILES = cub3d player

SRC = $(addprefix $(SRC_DIR)/, $(FILES:=.c))
OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
HEADER = $(INC_DIR)/cub3d.h
INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

#Colors:
GREEN		=	\033[92;5;118m
YELLOW		=	\033[93;5;226m
GRAY		=	\033[33;2;37m
RESET		=	\033[0m
CURSIVE		=	\033[33;3m

.PHONY: all clean fclean re norm libft mlx

all: libft mlx $(NAME)

libft:
	@printf "$(CURSIVE)$(GRAY) 	- Making libft... $(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(GREEN)    - Libft ready.\n$(RESET)"

mlx:
	@printf "$(CURSIVE)$(GRAY) 	- Making mlx... $(RESET)\n"
	@$(MAKE) -C $(MLX_DIR)
	@printf "$(GREEN)    - Mlx ready.\n$(RESET)"

$(NAME): $(LIBFT) $(MLX) $(OBJ) $(HEADER)
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	@$(CC) $(OBJ) $(INCLUDES) -o $(NAME) $(LDFLAGS) $(LIBFT) $(MLX)
	@printf "$(GREEN)    - Executable ready.\n$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJDIR)
	@printf "$(CURSIVE)$(GRAY) 	- Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rmdir --ignore-fail-on-non-empty $(OBJDIR)

norm:
	@printf "$(CURSIVE)$(GRAY)  - Running norminette (excluding mlx)...$(RESET)\n"
	@find $(INC_DIR) $(SRC_DIR) -type f \( -name "*.c" -o -name "*.h" \) ! -path "$(INC_DIR)/mlx/*" -exec norminette {} +
	@printf "$(GREEN)  - Norminette check done.$(RESET)\n"

fclean: clean
	@ $(RM) $(NAME)
	@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
	@printf "$(CURSIVE)$(GRAY)	- Rebuilding project... $(RESET)\n"
	@printf "$(GREEN)    - Project rebuilt successfully.$(RESET)\n"

.PHONY: all clean fclean re
