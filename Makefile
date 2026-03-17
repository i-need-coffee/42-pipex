# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjolliet <sjolliet@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/03 16:15:52 by sjolliet          #+#    #+#              #
#    Updated: 2026/03/17 21:50:09 by sjolliet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
BONUS_NAME		= pipex_bonus

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -Iinclude -Ilibft/include
BONUS_CFLAGS	= -Wall -Wextra -Werror -g -Ibonus/include -Ilibft/include

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a

SRC_DIR			= src
OBJ_DIR			= obj

BONUS_SRC_DIR	= bonus/src
BONUS_OBJ_DIR	= bonus/obj

SRCS			= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/pipe.c \
	$(SRC_DIR)/exec.c \
	$(SRC_DIR)/args.c

BONUS_SRCS		= \
	$(BONUS_SRC_DIR)/main_bonus.c \
	$(BONUS_SRC_DIR)/utils_bonus.c \
	$(BONUS_SRC_DIR)/pipe_bonus.c \
	$(BONUS_SRC_DIR)/exec_bonus.c \
	$(BONUS_SRC_DIR)/args_bonus.c \
	$(BONUS_SRC_DIR)/fork_bonus.c

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS		= $(BONUS_SRCS:$(BONUS_SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# **************************************************************************** #

all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	@echo "📚 Building Libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "🚀 Pipex compiled successfully!"

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(BONUS_CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
	@echo "✨ Pipex bonus compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@$(CC) $(BONUS_CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all bonus clean fclean re