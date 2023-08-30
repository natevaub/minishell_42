/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:52:23 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 20:27:50 by ckarl            ###   ########.fr       */
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
		if (shell->hd_docs)
			free_linked_list(shell->hd_docs);
		if (shell->hd_words)
			free_linked_list(shell->hd_docs);
		shell->hd_docs = NULL;
		shell->hd_words = NULL;
	}
	if (shell->p)
	{
		free(shell->p);
		shell->p = NULL;
	}
	free(prompt);
}
