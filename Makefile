NAME1 = server
NAME2 = client
CFLAGS = -Wall -Wextra -Werror
SRC1 = server.c utils.c
SRC2 = client.c utils.c
CC = cc
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all: $(NAME1) $(NAME2)

$(NAME1):$(OBJ1)
	$(CC) $(CFLAGS) -o $(NAME1) $(OBJ1)
	@echo "Server compiled successfully."

$(NAME2):$(OBJ2)
	$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2)
	@echo "Client compiled successfully."

clean:
	$(RM)  $(OBJ1) $(OBJ2)

fclean: clean
	$(RM) $(NAME1) $(NAME2)

re: fclean all

.PHONY: all clean fclean re