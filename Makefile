# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rnijhuis <rnijhuis@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/12 11:05:57 by rnijhuis      #+#    #+#                  #
#    Updated: 2022/03/12 16:26:32 by rubennijhui   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#=====================================#
#========= General variables =========#
#=====================================#

NAME := minishell
INCLUDE_DIR := include
SRC_DIR := src
LIBS_DIR := libs
OBJS_DIR := objs

#=====================================#
#============ Input files ============#
#=====================================#

READLINE_DIR = /usr/local/Cellar/readline/8.1.2

LIBS := $(LIBS_DIR)/LibFT/libft.a
LIBS_HEADERS := -I$(LIBS_DIR)/LibFT/include/ \
				-I $(READLINE_DIR)/include/ \
				-I/Users/mjoosten/.brew/opt/readline/include/

INC := -I $(INCLUDE_DIR) $(LIBS_HEADERS)

SRCS := main.c

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g $(INC)
LDFLAGS = -L $(READLINE_DIR)/lib/ -lreadline

#=====================================#
#=============== Rules ===============#
#=====================================#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

$(NAME):$(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "✅ Built $(NAME)"

$(LIBS_DIR)/LibFT/libft.a:
	@make -C $(LIBS_DIR)/LibFT

install_submodules:
	@git submodule update --init --recursive

run: $(NAME)
	./$(NAME)

clean:
	@make clean -C $(LIBS_DIR)/LibFT
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C $(LIBS_DIR)/LibFT
	@rm -f $(NAME)

re: fclean all

.PHONY: all re run clean fclean
