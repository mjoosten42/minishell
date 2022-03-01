NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LIBFT = libft/libft.a

SRC = 	main.c		\
		commands.c	

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $^ $(LIBFT) -o $@ -lreadline #-L/Users/mjoosten/.brew/opt/readline/lib

$(LIBFT):
	make -C libft
	make clean -C libft

%.o: %.c
	$(CC) $(FLAGS) -c $^ #-I/Users/mjoosten/.brew/opt/readline/include/

clean:
	make fclean -C libft
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re
