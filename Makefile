CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

CLIENT = client
SERVER = server

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

all: $(CLIENT) $(SERVER)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(CLIENT): $(LIBFT) $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJ) -L$(LIBFT_DIR) -lft

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJ) -L$(LIBFT_DIR) -lft

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $(CLIENT_SRC) -I$(LIBFT_DIR)

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $(SERVER_SRC) -I$(LIBFT_DIR)

bonus:
	@$(MAKE) CLIENT_SRC=client_bonus.c SERVER_SRC=server_bonus.c
	
clean:
	rm -f *.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re