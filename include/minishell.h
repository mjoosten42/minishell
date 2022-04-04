/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:10 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/04 11:06:35 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <limits.h>
# include <unistd.h>
# include <signal.h>

// Special chars
# define META_CHARS "|<>$\"\' \t\n"

// Token definitions
enum e_symbol {
	pipe_char,
	red_in,
	red_out,
	dollar,
	dquote,
	quote,
	space,
	tab,
	newline,
	heredoc,
	red_out_app,
	file_descriptor,
	word,
	start
};

// Program data
typedef struct s_program_data
{
	char			**env;
	char			*dir;
	int				amount_env_lines;
	int				last_exit_status;
}					t_program_data;

// Token used for lexer
typedef struct s_token
{
	enum e_symbol	type;
	int				position;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

// Global var
extern t_program_data	g_pd;

//	readline
void	rl_replace_line(const char *text, int clear_undo);
int		rl_on_new_line(void);

//	Main
pid_t	ft_exec(char **args, int fds[2]);

//	Lexer
void	lexer(t_token *head, char *str);

//	Expand
void	ft_expand(t_token *token);

//	Parser
void	ft_parse(t_token *head, int pipefd);
void	ft_remove_token(t_token *token);

//	Path
char	*ft_getpath(char *str);

//	Heredoc
void	ft_heredoc(t_token *head);

//	Builtins
void	echo(char **strs);
void	cd(char *path);
void	pwd(void);
void	export(char *variable);
void	unset(char *str);
void	env(void);
void	ft_exit(char *str);
int		is_builtin(char **strs);

// Utils
void	print_tokens(t_token *token);
pid_t	ft_fork(void);
int		ft_open(const char *path, int oflag, mode_t mode);

#endif
