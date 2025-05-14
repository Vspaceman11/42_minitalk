# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpushkar <vpushkar@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 16:25:43 by vpushkar          #+#    #+#              #
#    Updated: 2025/05/12 15:47:51 by vpushkar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = server
NAME2 = client

CC = gcc
BUFFER_SIZE ?= 30000
CFLAGS = -Wall -Wextra -Werror -g -DBUFFER_SIZE=$(BUFFER_SIZE)

LIBFT_DIR = libft_extended
LIBFT_REPO = https://github.com/Vspaceman11/libft_extended.git
LIBFT_A = $(LIBFT_DIR)/libft_extended.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC1 = server.c
SRC2 = client.c

SRCS1 = $(addprefix $(SRC_DIR)/, $(SRC1))
SRCS2 = $(addprefix $(SRC_DIR)/, $(SRC2))

OBJ1 = $(addprefix $(OBJ_DIR)/, $(SRC1:.c=.o))
OBJ2 = $(addprefix $(OBJ_DIR)/, $(SRC2:.c=.o))

RM = rm -f

all: $(LIBFT_A) $(NAME1) $(NAME2)

$(LIBFT_A):
	test -d $(LIBFT_DIR) || git clone --depth=1 $(LIBFT_REPO) $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/inc -c $< -o $@

$(NAME1): $(OBJ1) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ1) -L$(LIBFT_DIR) -lft_extended -I$(INC_DIR) -I$(LIBFT_DIR)/inc -o $@

$(NAME2): $(OBJ2) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ2) -L$(LIBFT_DIR) -lft_extended -I$(INC_DIR) -I$(LIBFT_DIR)/inc -o $@

clean:
	$(RM) $(OBJ1) $(OBJ2)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean || true

fclean: clean
	$(RM) $(NAME1) $(NAME2)
	$(MAKE) -C $(LIBFT_DIR) fclean || true
	@if [ "$(REMOVE_LIBFT)" == "1" ]; then \
		echo "Removing libft_extended directory."; \
		rm -rf $(LIBFT_DIR); \
	else \
		echo "Keeping libft_extended directory."; \
	fi

re: fclean all

.PHONY: all clean fclean re
