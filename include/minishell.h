/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjoosten <mjoosten@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 14:57:10 by mjoosten      #+#    #+#                 */
/*   Updated: 2022/03/22 14:46:29 by rnijhuis      ########   odam.nl         */
=======
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:10 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/22 15:15:01 by mjoosten         ###   ########.fr       */
>>>>>>> 67b5e1ee961566d774c57204cff86b4fd3f41917
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <stdio.h>
# include <limits.h>

// Special chars
# define META_CHARS "|<>$\"\' \t\n"

// Token definitions
enum e_symbol {
	word,
	pipe_char,
	red_in,
	red_out,
	here_doc,
	red_out_app,
	dollar,
	dquote,
	quote,
	space,
	tab,
	newline
};

// Program data
typedef struct s_program_data
{
	char			**env;
	char			*current_dir;
	int				amount_env_lines;
}				t_program_data;

// Token used for lexer
typedef struct s_token
{
	enum e_symbol	type;
	int				position;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

//	readline
void	rl_replace_line(const char *text, int clear_undo);
int		rl_on_new_line(void);

//	Main
void	ft_signal(int signum);
void	print_tokens(t_token *token);

//	Path
char	*ft_getpath(char *str);
char	**ft_getpaths(void);

//	Lexer
void	lexer(t_token **head, char *str);

//	Parser
void	ft_parse(t_token **head);

//	Builtins
void	ft_echo(char **strs);
void	ft_exit(void);

#endif
