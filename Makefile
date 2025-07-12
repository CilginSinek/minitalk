NAME1 = server
NAME2 = client
BONUS1 = server_bonus
BONUS2 = client_bonus
CFLAGS = -Wall -Wextra -Werror
BONUSSRC1 = server_bonus.c utils.c
BONUSSRC2 = client_bonus.c utils.c
BONUSOBJ1 = $(BONUSSRC1:.c=.o)
BONUSOBJ2 = $(BONUSSRC2:.c=.o)
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

bonus: $(BONUS1) $(BONUS2)

$(BONUS1): $(BONUSOBJ1)
	$(CC) $(CFLAGS) -o $(BONUS1) $(BONUSOBJ1)
	@echo "Bonus Server compiled successfully."

$(BONUS2): $(BONUSOBJ2)
	$(CC) $(CFLAGS) -o $(BONUS2) $(BONUSOBJ2)
	@echo "Bonus Client compiled successfully."

clean:
	$(RM)  $(OBJ1) $(OBJ2) $(BONUSOBJ1) $(BONUSOBJ2)

fclean: clean
	$(RM) $(NAME1) $(NAME2) $(BONUS1) $(BONUS2)
	@echo "All executables removed."

re: fclean all

.PHONY: all clean fclean re