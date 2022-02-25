NAME = minishell
FLAGS = -Wall -Werror -Wextra -g
LIBFT = libft/libft.a

SRC = 	main.c		\
		commands.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) $^ $(LIBFT) -o $@ -lreadline #-L/Users/mjoosten/.brew/opt/readline/lib

$(LIBFT):
	make -C libft
	make clean -C libft

%.o: %.c
	gcc $(FLAGS) -c $^ #-I/Users/mjoosten/.brew/opt/readline/include/

clean:
	make fclean -C libft
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re
