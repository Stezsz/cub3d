# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: strodrig <strodrig@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 17:44:25 by tborges-          #+#    #+#              #
#    Updated: 2025/06/04 15:24:37 by strodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
INCLUDE		= ft_printf.h
CC			= cc
CFLAGS		= -Wall -Werror -Wextra

SRCS = ft_printf.c prints1.c prints2.c prints3.c
OBJS	= $(SRCS:.c=.o)

GREEN		=	\033[92;5;118m
YELLOW		=	\033[93;5;226m
GRAY		=	\033[33;2;37m
RESET		=	\033[0m
CURSIVE		=	\033[33;3m

$(NAME):	$(OBJS) $(INCLUDE)
	@ar -rcs $(NAME) $(OBJS)

%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

clean:
	@rm -f $(OBJS)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
