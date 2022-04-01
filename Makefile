# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 11:05:57 by rnijhuis          #+#    #+#              #
#    Updated: 2022/04/01 16:47:42 by mjoosten         ###   ########.fr        #
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

READLINE_DIR = -L/Users/$(USER)/.brew/opt/readline/lib

LIBS := $(LIBS_DIR)/libft/libft.a

LIBS_HEADERS := -I $(LIBS_DIR)/libft/include/					\
				-I $(READLINE_DIR)/include/						\
				-I /Users/$(USER)/.brew/opt/readline/include/

INC := -I $(INCLUDE_DIR) $(LIBS_HEADERS)

SRCS :=	main.c					\
		lexer.c					\
		parser.c				\
		expand.c				\
		path.c					\
		here_doc.c				\
		builtin/echo.c			\
		builtin/cd.c			\
		builtin/pwd.c			\
		builtin/env.c			\
		builtin/export.c		\
		builtin/unset.c			\
		builtin/exit.c			\
		builtin/run_builtin.c	\
		utils/print_tokens.c	\

OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

#=====================================#
#========= Command arguments =========#
#=====================================#

CC = gcc
CFLAGS = -Wall -Werror -Wextra $(INC) -g
LDFLAGS = $(READLINE_DIR) -lreadline

#=====================================#
#=============== Rules ===============#
#=====================================#

objs/%.o:src/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $^
	@echo "🔨 Compiling: $^"
	
all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "✅ Built $(NAME)"

$(LIBS_DIR)/libft/libft.a:
	@make -C $(LIBS_DIR)/libft

submodules:
	@git submodule update --init --recursive
	@cd $(LIBS_DIR)/libft/ && git pull

run: $(NAME)
	@./$(NAME)

clean:
	@make clean -C $(LIBS_DIR)/libft
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C $(LIBS_DIR)/libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all re run clean fclean
