/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjoosten <mjoosten@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 14:57:10 by mjoosten      #+#    #+#                 */
/*   Updated: 2022/03/21 14:19:09 by rnijhuis      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

enum e_symbol {
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

void	ft_execute(char *str);
char	**ft_getpaths(void);
char	*ft_getpath(char *str);

void	lexer(t_token **head, char *str);
void	get_tokens(char *str);

#endif
