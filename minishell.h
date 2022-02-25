/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:57:10 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/25 15:03:51 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

# define BACKSPACE 8

	//	main.c
void	ft_eof(void);
void	ft_error(char *str);

	//	commands.c
void	ft_execute(char *str);
char	**ft_getpaths(void);
char	*ft_getpath(char *str);

#endif