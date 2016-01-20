# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/13 11:09:09 by nschilli          #+#    #+#              #
#    Updated: 2016/01/13 16:23:53 by nschilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GCC = gcc

CFLAGS	= -Wall -Wextra -Werror -O3 -g

SERVEUR = serveur
CLIENT = client

SERVEUR_DIR = serveur_dir
CLIENT_DIR = client_dir

SRC_DIR = /srcs/
INC_DIR = includes/

SERVEUR_FILE =	main.c \
				manager_clients.c \
				handle_event.c \
				manager_commands.c \
				command.c \
				check.c \

SERVEUR_SRC = $(addprefix $(SERVEUR_DIR)/$(SRC_DIR), $(SERVEUR_FILE))

SERVEUR_OBJ = $(SERVEUR_SRC:.c=.o)

CLIENT_FILE = main.c \
			  name.c \
			  handle_event.c \

CLIENT_SRC = $(addprefix $(CLIENT_DIR)/$(SRC_DIR), $(CLIENT_FILE))

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: $(SERVEUR) $(CLIENT)

$(SERVEUR): $(SERVEUR_OBJ)
	@make -C libft/
	@$(GCC) $(CFLAGS) -o $(SERVEUR) $(SERVEUR_OBJ) libft/libft.a
	@echo "\033[33m"compilation of $(SERVEUR) : "\033[32m"Success"\033[0m"

$(CLIENT): $(CLIENT_OBJ)
	@make -C libft/
	@$(GCC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) libft/libft.a
	@echo "\033[33m"compilation of $(CLIENT) : "\033[32m"Success"\033[0m"

%.o: %.c
	@echo -n .
	@$(GCC) $(CFLAGS) -c -o $@ $^ -I $(SERVEUR_DIR)/$(INC_DIR) -I $(CLIENT_DIR)/$(INC_DIR)

clean:
	@make -C libft/ clean
	@rm -f $(SERVEUR_OBJ)

fclean: clean
	@make -C libft/ fclean
	@rm -rf $(SERVEUR) $(CLIENT)
	@echo "\033[31m"$(SERVEUR) and $(CLIENT) : deleted"\033[0m"

re: fclean all

.PHONY: clean fclean re
