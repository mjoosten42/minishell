/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:10 by mjoosten          #+#    #+#             */
/*   Updated: 2022/03/14 15:25:27 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

# define BACKSPACE 8

	//	readline
void	rl_replace_line(const char *text, int clear_undo);
int		rl_on_new_line(void);

void	ft_execute(char *str);
char	**ft_getpaths(void);
char	*ft_getpath(char *str);

#endif