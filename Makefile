NAME = minishell
FLAGS = -Wall -Werror -Wextra
SRC = main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
	gcc $(FLAGS) -o $@

%.o: %.c
	gcc $(FLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re