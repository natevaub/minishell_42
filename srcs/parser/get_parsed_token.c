/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 02:38:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 19:53:56 by ckarl            ###   ########.fr       */
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
			shell->cmd = ft_newlst_cmd(ft_init_cmds(&parse));
		}
		else
		{
			ft_lstadd_back_cmd(&shell->cmd,
				ft_newlst_cmd(ft_init_cmds(&parse)));
		}
	}
	shell->token = start;
}

void	ft_parsing(t_minishell *shell, char *prompt)
{
	shell->syntax = 0;
	ft_tokenize_prompt(shell, prompt);
	if (ft_heredoc_detected(shell) == 1)
	{
		ft_init_hd_signals(&signal_heredoc_handler);
		ft_heredoc(shell);
		shell->heredoc = 1;
		ft_init_signals(signal_exec_handler);
		if (g_status != 0)
		{
			shell->last_exit_status = g_status;
			return ;
		}
	}
	if (shell->syntax == 0)
	{
		ft_expand_token(shell);
		if (ft_syntax_checker(shell) == 0)
		{
			ft_trim_quote(shell);
			ft_join_tk(shell->token);
			ft_parse_token(shell);
		}
	}
}
