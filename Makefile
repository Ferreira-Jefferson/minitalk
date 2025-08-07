# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:41:00 by jtertuli          #+#    #+#              #
#    Updated: 2025/08/07 16:41:24 by jtertuli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Executable names
CLIENT = client
SERVER = server

# Library path
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source files
CLIENT_SRC = client.c
SERVER_SRC = server.c

# Object files
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

# Default target
all: $(CLIENT) $(SERVER)

# Build libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Build client executable
$(CLIENT): $(LIBFT) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJ) -L$(LIBFT_DIR) -lft

# Build server executable
$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJ)

# Compile client object file
$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -I$(LIBFT_DIR)

# Compile server object file
$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $(SERVER_SRC)

# Clean object files
clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

# Clean all generated files
fclean: clean
	rm -f $(CLIENT) $(SERVER)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re