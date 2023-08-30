/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:54:02 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 17:58:24 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc(t_minishell *shell)
{
	char			*content;
	t_linked_list	*del;

	del = ft_get_heredocs(shell->token);
	shell->hd_docs = del;
	while (del != NULL && g_status == 0)
	{
		if (ft_eof_quoted(del->value) == 1)
		{
			del->value = ft_strtrim(del->value, "\"'");
			shell->hd_words = ft_store_heredoc_content(del->value);
			content = ft_list_to_char(shell->hd_words);
		}
		else
		{
			shell->hd_words = ft_store_heredoc_content(del->value);
			content = ft_list_to_char_expands(shell->hd_words);
		}
		ft_write_to_temp_file(content);
		free_linked_list(shell->hd_words);
		del = del->next;
	}
	shell->hd_words = NULL;
}

int	ft_get_heredoc_temp_fd(t_tok **tk)
{
	int	fd;

	fd = open(".heredoc", O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("Error opening .hereodc file\n");
		exit(EXIT_FAILURE);
	}
	while ((*tk)->next->type != E_STRING)
	{
		*tk = (*tk)->next;
	}
	*tk = (*tk)->next;
	return (fd);
}
