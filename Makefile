NAME = minishell
FLAGS = -Wall -Werror -Wextra -g
LIBFT = libft/libft.a
SRC = main.c
#READLINE_PATH = /Users/mjoosten/.brew/opt/readline	 -L/$(READLINE_PATH)/lib	 -I$(READLINE_PATH)/include/

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) $^ $(LIBFT) -o $@ -lreadline

$(LIBFT):
	make -C libft
	make clean -C libft

%.o: %.c
	gcc $(FLAGS) -c $^

clean:
	make fclean -C libft
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = clean fclean re