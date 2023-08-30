/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 17:54:33 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_infile_fd(t_tok **tk)
{
	char	*fd;

	fd = NULL;
	(*tk) = (*tk)->next;
	if ((*tk) == NULL)
		return (fd);
	while ((*tk)->type == E_SPACE)
	{
		if ((*tk)->next == NULL)
		{
			(*tk) = (*tk)->next;
			break ;
		}
		(*tk) = (*tk)->next;
	}
	if ((*tk) != NULL)
		fd = (*tk)->word;
	return (fd);
}

char	*ft_get_outfile_fd(t_tok **tk)
{
	char	*fd;

	fd = NULL;
	(*tk) = (*tk)->next;
	if (*tk == NULL)
		return (fd);
	while ((*tk)->type == E_SPACE)
	{
		if ((*tk)->next == NULL)
		{
			(*tk) = (*tk)->next;
			break ;
		}
		(*tk) = (*tk)->next;
	}
	if ((*tk) != NULL)
	{
		fd = (*tk)->word;
	}
	return (fd);
}

void	ft_open_files_redirection(t_tok **tk, t_cmd *cmd)
{
	if (ft_strcmp((*tk)->word, D_INFILE) == 0)
	{
		cmd->infile = ft_get_infile_fd(tk);
	}
	else if (ft_strcmp((*tk)->word, D_OUTFILE) == 0)
	{
		cmd->outfile = ft_get_outfile_fd(tk);
	}
	else if (ft_strcmp((*tk)->word, D_APPEND) == 0)
	{
		cmd->outfile = ft_get_outfile_fd(tk);
		cmd->append = 1;
	}
	else
	{
		cmd->infile = ".heredoc";
		cmd->read = ft_get_heredoc_temp_fd(tk);
	}
	if ((*tk) != NULL)
		((*tk)) = (*tk)->next;
}
