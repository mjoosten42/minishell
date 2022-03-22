/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:10 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/22 11:56:35 by mjoosten         ###   ########.fr       */
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
	here_doc,
	red_out,
	red_out_app,
	dollar,
	dquote,
	quote,
	space,
	tab,
	newline
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

#endif
