/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:10:47 by rnijhuis          #+#    #+#             */
/*   Updated: 2022/03/29 14:11:21 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_tokens(t_token *token)
{
	char	*types[] = {
		"pipe_char",
		"red_in",
		"red_out",
		"dollar",
		"dquote",
		"quote",
		"space",
		"tab",
		"newline",
		"here_doc",
		"red_out_app",
		"file_descriptor",
		"word"
	};

	if (token)
	{
		printf(" - id ------------ type - value\n");
		while (token)
		{
			printf(" | %2i | %15s | [%s]\n",
				token->position, types[token->type], token->value);
			token = token->next;
		}
		printf("\n");
	}
}
