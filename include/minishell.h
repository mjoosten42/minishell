/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjoosten <mjoosten@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 14:57:10 by mjoosten      #+#    #+#                 */
/*   Updated: 2022/03/21 15:39:23 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <stdio.h>
# include <limits.h>

// Special chars
#define SPECIAL_CHARS " \"\'><|$"
#define WORD_END "\t \"\'><|$"

// Token definitions
enum e_symbol {
	space,
	word,
	quote,
	dquote,
	red_in,
	red_out,
	red_out_app,
	here_doc,
	pipe_char,
	dollar
};

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

// Utils
char	*ft_getpath(char *str);

// Lexer
void	print_tokens(t_token *token);
void	lexer(t_token **head, char *str);

// Parser
void	ft_parse(t_token *head);

#endif
