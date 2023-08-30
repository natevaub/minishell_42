/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 13:32:44 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_infile_fd(t_tok **tk, t_minishell *ms)
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

char	*ft_get_outfile_fd(t_tok **tk, t_minishell *ms)
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

// int	ft_get_append_outfile_fd(t_tok **tk, t_minishell *ms)
// {
// 	char	*fd;

// 	fd = NULL;
// 	(*tk) = (*tk)->next;
// 	if (*tk == NULL)
// 		return (fd);
// 	while ((*tk)->type == E_SPACE)
// 	{
// 		if ((*tk)->next == NULL)
// 		{
// 			(*tk) = (*tk)->next;
// 			break ;
// 		}
// 		(*tk) = (*tk)->next;
// 	}
// 	if ((*tk) != NULL)
// 	{
// 		fd = (*tk)->word;
// 		fd = open((*tk)->word, O_CREAT | O_APPEND | O_RDWR, 0644);
// 		if (fd == -1)
// 			ft_permission_denied((*tk)->word, ms);
// 		// else
// 		// 	ms->last_exit_status = 0;
// 	}
// 	return (fd);
// }

void	ft_open_files_redirection(t_tok **tk, t_cmd *cmd, t_minishell *ms)
{
	if (ft_strcmp((*tk)->word, D_INFILE) == 0)
	{
		cmd->infile = ft_get_infile_fd(tk, ms);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
	else if (ft_strcmp((*tk)->word, D_OUTFILE) == 0)
	{
		cmd->outfile = ft_get_outfile_fd(tk, ms);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
	else if (ft_strcmp((*tk)->word, D_APPEND) == 0)
	{
		cmd->outfile = ft_get_outfile_fd(tk, ms);
		cmd->append = 1;
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
	else
	{
		cmd->infile = ".heredoc";
		cmd->read = ft_get_heredoc_temp_fd(tk);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
}
