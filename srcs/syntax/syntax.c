/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:34:13 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 11:29:47 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_print_error(err, shell);
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
			return (1);
		}
		else if (ft_syntax_red_check(tok) == 2)
		{
			return (2);
		}
		else if (ft_syntax_quote_check(tok->word) == 1)
		{
			return (3);
		}
		else if (ft_syntax_pipe_check(tok) == 1)
		{
			return (4);
		}
		tok = tok->next;
	}
	return (0);
}

void	ft_print_error(int err, t_minishell *ms)
{
	ms->last_exit_status = 258;
	if (err == 1)
	{
		ft_putstr_fd("minishell : syntax error \
		near unexpected token `<' or `>'\n", 2);
	}
	else if (err == 2)
	{
		ft_putstr_fd \
		("minishell : syntax error near unexpected token `<<' or `>>'\n", 2);
	}
	else if (err == 3)
	{
		ft_putstr_fd \
		("minishell : syntax error open quote not being closed\n", 2);
	}
	else if (err == 4)
	{
		ft_putstr_fd \
		("minishell : syntax error near unexpected token `|'\n", 2);
	}
}
