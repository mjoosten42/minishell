/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rnijhuis <rnijhuis@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/28 14:10:47 by rnijhuis      #+#    #+#                 */
/*   Updated: 2022/03/28 14:35:21 by rnijhuis      ########   odam.nl         */
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
		"word"
	};

	if (token)
	{
		printf(" - id -------- type - value\n");
		while (token)
		{
			printf(" | %2i | %11s | [%s]\n",
				token->position, types[token->type], token->value);
			token = token->next;
		}
		printf("\n");
	}
}
