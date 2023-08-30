/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 11:18:16 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_infile_fd(t_tok **tk, t_minishell *ms)
{
	int	fd;

	fd = 0;
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
		fd = open((*tk)->word, O_RDONLY);
	if (fd == -1)
		ft_open_failed((*tk)->word, ms);
	else
		ms->last_exit_status = 0;
	return (fd);
}

int	ft_get_outfile_fd(t_tok **tk, t_minishell *ms)
{
	int	fd;

	fd = 1;
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
		fd = open((*tk)->word, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		ft_permission_denied((*tk)->word, ms);
	else
		ms->last_exit_status = 0;
	return (fd);
}

int	ft_get_append_outfile_fd(t_tok **tk, t_minishell *ms)
{
	int	fd;

	fd = 1;
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
		fd = open((*tk)->word, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd == -1)
		ft_permission_denied((*tk)->word, ms);
	else
		ms->last_exit_status = 0;
	return (fd);
}

void	ft_open_files_redirection(t_tok **tk, t_cmd *cmd, t_minishell *ms)
{
	if (ft_strcmp((*tk)->word, D_INFILE) == 0)
	{
		cmd->read = ft_get_infile_fd(tk, ms);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
	else if (ft_strcmp((*tk)->word, D_OUTFILE) == 0)
	{
		cmd->write = ft_get_outfile_fd(tk, ms);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
	else if (ft_strcmp((*tk)->word, D_APPEND) == 0)
	{
		cmd->write = ft_get_append_outfile_fd(tk, ms);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
	else
	{
		cmd->read = ft_get_heredoc_temp_fd(tk);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
}
