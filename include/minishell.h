#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <unistd.h>

// Special chars
# define META_CHARS "|<>$\"\' \t\n"

// Token definitions
typedef enum e_symbol {
	pipe_char,
	red_in,
	red_out,
	dollar,
	dquote,
	quote,
	space,
	tab,
	newline,
	here_doc,
	red_out_app,
	word,
	start
}	t_type;

// Program data
typedef struct s_program_data
{
	char	**env;
	char	*pwd;
	int		amount_env_lines;
	int		last_exit_status;
	int		active_processes;
	int		heredoc_sigint;
}			t_program_data;

// Token used for lexer
typedef struct s_token
{
	enum e_symbol	type;
	int				position;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

//	Programdata
t_program_data	*pd_get(void);
void			pd_clear(void);

//	readline
void			rl_replace_line(const char *text, int clear_undo);
int				rl_on_new_line(void);

//	Exec
void			ft_exec(char **args, int fds[2]);

//	Lexer
void			ft_lexer(t_token *head, char *str);

//	Expand
int				ft_expand(t_token *head);
char			*ft_get_env_from_pd(char *str);

//	Parser
void			ft_parse(t_token *head, int pipefd);

//	Heredoc
int				ft_here_doc(t_token *head, int *fd);

//	Utils
int				export_name_len(char *str);

//	Builtins
int				is_builtin_unforked(char **strs);
int				is_builtin_forked(char **strs);
void			echo(char **strs);
void			cd(char *path);
void			pwd(void);
void			export(char *variable);
void			unset(char *str);
void			env(void);
void			ft_exit(char *str);

// Token
t_token			*token_start(void);
int				token_add_back(t_token *token, t_token *new_token);
void			ft_remove_token(t_token *token);
void			print_tokens(t_token *token);

// Syscalls
pid_t			ft_fork(void);
int				ft_pipe(int fildes[2]);
int				ft_dup2(int fildes, int fildes2);
int				ft_open(const char *path, int oflag, mode_t mode);
int				ft_close(int fildes);

// Errors
int				ft_exit_string(char *str, int exit_code);
int				ft_return_error(char *str);
int				nop(void);

#endif
