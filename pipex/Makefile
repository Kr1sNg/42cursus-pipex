# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 11:14:07 by tat-nguy          #+#    #+#              #
#    Updated: 2025/05/23 23:27:15 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

# Libft
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Source Files
SRC_DIR = src
SRC     = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
BNS_DIR = bonus
BNS_SRC = $(foreach dir, $(BNS_DIR), $(wildcard $(dir)/*.c))


# Object Files
OBJS 	= $(SRC:.c=.o)
OBJ_BNS = $(BNS_SRC:.c=.o)

# Include and Flags
INCLUDE = -Iincludes
CFLAGS 	= -Wall -Wextra -Werror
CC 		= cc
RM		= rm -rf

# Target
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

bonus: $(LIBFT) $(OBJ_BNS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o pipex_bonus $(OBJ_BNS) -L$(LIBFT_DIR) -lft

# Clean
clean:
	@$(RM) $(OBJS) $(OBJ_BNS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME) pipex_bonus
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
