/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:22:18 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/21 15:23:14 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_token(t_minishell **shell)
{
	t_tok	*curr;
	t_tok	*next;

	curr = (*shell)->token;
	next = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->word)
			free(curr->word);
		if (curr)
			free(curr);
		curr = next;
	}
	(*shell)->token = NULL;
}

void	ft_free_cmd(t_minishell *shell)
{
	// printf("In ft free cmd\n");
	t_lcmd	*curr;
	t_lcmd	*next;
	int		i;

	curr = (shell)->cmd;
	next = NULL;
	while(curr != NULL)
	{
		i = 0;
		next = curr->next;
		// while (curr->option[i]!= NULL)								//check why this gives error: pointer freed was not allocated
		// {
		// 	free(curr->option[i]);
		// 	i++;
		// }
		// printf("curr->option[0]: %s", curr->option[0]);
		if (curr->option)
			free(curr->option);
		// free_two_dimension_array(curr->option);
		if (curr)
			free(curr);
		curr = next;
	}
	(shell)->cmd = NULL;
}

void	ft_free_parsing(t_minishell *shell)
{
	ft_free_cmd(shell);
	ft_free_token(&shell);
	if (shell->heredoc == 1)
	{
		unlink(".heredoc");
		shell->heredoc = 0;
	}
}
