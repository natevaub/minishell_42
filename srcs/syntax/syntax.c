#include "../includes/minishell.h"

int	ft_syntax_checker(t_minishell *shell)
{
	t_tok	*curr;
	int		err;

	curr = shell->token;
	err = 0;
	err = ft_look_for_err(shell->token);
	if (err != 0)
	{
		shell->syntax = 1;
		shell->token = curr;
		ft_print_error(err);
		return (1);
	}
	shell->syntax = 0;
	shell->token = curr;
	return (0);
}

int	ft_look_for_err(t_tok *tok)
{
	while (tok != NULL)
	{
		if (ft_syntax_red_check(tok) == 1)
		{
			printf("1\n");
			return (1);
		}
		else if (ft_syntax_red_check(tok) == 2)
		{
			printf("2\n");
			return (2);
		}
		else if (ft_syntax_quote_check(tok->word) == 1)
		{
			printf("3\n");
			return (3);
		}
		else if (ft_syntax_pipe_check(tok) == 1)
		{
			printf("4\n");
			return (4);
		}
		tok = tok->next;
	}
	return (0);
}

void	ft_print_error(int err)
{
	if (err == 1)
		ft_putstr_fd("minishell : syntax error near unexpected token `<' or `>'\n", 2);
	else if (err == 2)
		ft_putstr_fd("minishell : syntax error near unexpected token `<<' or `>>'\n", 2);
	else if (err == 3)
	{
		ft_putstr_fd("minishell : syntax error open quote not being closed\n", 2);
	}
	else if (err == 4)
	{
		ft_putstr_fd("minishell : syntax error near unexpected token `|'\n", 2);
	}
}
