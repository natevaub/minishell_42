/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:54:02 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/20 22:23:34 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc(t_minishell *shell)
{
	char			*content;
	t_linked_list	*del;
	t_linked_list	*node;
	
	if (ft_heredoc_detected(shell) == 1)
	{
		shell->heredoc = 1;
		del = ft_get_heredocs(shell->token);
		while (del != NULL)
		{
			if (ft_eof_quoted(del->value) == 1)
			{

				del->value = ft_strtrim(del->value, "\"'");
				node = ft_store_heredoc_content(del->value);
				content = ft_list_to_char(node);
				ft_write_to_temp_file(content);
			}
			else
			{
				node = ft_store_heredoc_content(del->value);
				content = ft_list_to_char_expands(node);
				ft_write_to_temp_file(content);
			}
			del = del->next;
		}
	}
}

int	ft_get_heredoc_temp_fd(t_tok **tk, t_minishell *ms)
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