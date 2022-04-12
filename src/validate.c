#include "minishell.h"
#include "libft.h"

int	ft_validate(t_token *token)
{
	t_type	type;

	while (token)
	{
		type = token->type;
		if (type == red_in || type == red_out
			|| type == here_doc || type == red_out_app)
		{
			if (!token->next || token->next->type != word)
				return (ft_put_syntax_error("expected redirect target"));
			token = token->next;
		}
		if (type == pipe_char)
		{
			if (token->prev->type == start)
				return (ft_put_syntax_error("expected command before pipe"));
			if (!token->next || token->next->type == pipe_char)
				return (ft_put_syntax_error("expected command after pipe"));
		}
		token = token->next;
	}
	return (0);
}

int	ft_put_syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}

void	ft_put_type_fd(t_type type, int fd)
{
	char	*types[13];

	types[0] = "pipe_char";
	types[1] = "red_in";
	types[2] = "red_out";
	types[3] = "dollar";
	types[4] = "dquote";
	types[5] = "quote";
	types[6] = "space";
	types[7] = "tab";
	types[8] = "newline";
	types[9] = "here_doc";
	types[10] = "red_out_app";
	types[11] = "word";
	types[12] = "start";
	ft_putchar_fd('`', fd);
	ft_putstr_fd(types[type], fd);
	ft_putchar_fd('\'', fd);
	ft_putchar_fd('\n', fd);
}
