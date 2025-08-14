# Simple Makefile for testing map reading functionality

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = test_map

# Source files
SRCS = test_map.c map_read.c map_read_utils.c map_read_grid.c ft_lseek.c map_verify.c map_verify_aux.c map_verify_utils.c map_verify_memory.c
OBJS = $(SRCS:.c=.o)

# Include paths
INCLUDES = -I../../includes -I../../includes/libft/get_next_line

# Libraries
LIBFT_DIR = ../../includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = ../../includes/libft/get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(GNL_OBJS) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(GNL_OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

test: $(NAME)
	./$(NAME) ../../maps/default.cub

.PHONY: all clean fclean re test
