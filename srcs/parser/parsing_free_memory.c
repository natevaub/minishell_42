/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:52:23 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 02:17:25 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_token(t_minishell *shell)
{
	t_tok	*curr;
	t_tok	*next;

	curr = shell->token;
	next = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr)
		{
			free(curr->word);
			free(curr);
		}
		curr = next;
	}
	shell->token = NULL;
}

void	ft_free_cmd(t_minishell *shell)
{
	t_lcmd	*temp_cmd;
	t_lcmd	*next;

	temp_cmd = shell->cmd;
	next = NULL;
	while (temp_cmd != NULL)
	{
		next = temp_cmd->next;
		if (temp_cmd->option)
			free(temp_cmd->option);
		if (temp_cmd)
			free(temp_cmd);
		temp_cmd = next;
	}
	shell->cmd = NULL;
}

void	ft_free_parsing(t_minishell *shell, char *prompt)
{
	if (shell->token)
		ft_free_token(shell);
	if (shell->cmd)
		ft_free_cmd(shell);
	if (shell->heredoc == 1)
	{
		unlink(".heredoc");
		shell->heredoc = 0;
	}
	if (shell->p)
	{
		free(shell->p);
	}
	shell->p = NULL;
	free(prompt);
}
