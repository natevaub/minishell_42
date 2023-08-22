/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 02:38:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/22 22:54:57 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse_token(t_minishell *shell)
{
	t_tok	*start;
	t_tok	*parse;

	start = shell->token;
	parse = shell->token;
	while (parse != NULL)
	{
		if (!shell->cmd)
		{
			shell->cmd = ft_newlst_cmd(ft_init_cmds(&parse, shell));
		}
		else
		{
			ft_lstadd_back_cmd(&shell->cmd,
				ft_newlst_cmd(ft_init_cmds(&parse, shell)));
		}
	}
	shell->token = start;
}

void	ft_parsing(t_minishell *shell, char *prompt)
{
	int	err;

	shell->syntax = 0;
	ft_tokenize_prompt(shell, prompt);
	// if (DEBUG) ft_print_tokens(shell->token);
	if (ft_heredoc_detected(shell) == 1)
	{
		ft_heredoc(shell);
		shell->heredoc = 1;
	}
	err = 0;
	if (shell->syntax == 0)
	{
		ft_expand_token(shell);
		if (ft_syntax_checker(shell) == 0)
		{
			ft_trim_quote(shell);
			err = ft_join_tk(shell->token);
			ft_parse_token(shell);
		}
	}
}