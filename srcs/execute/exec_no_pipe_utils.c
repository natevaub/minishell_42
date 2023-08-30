/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 20:17:54 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_open_failed_single_cmd(t_lcmd *cmd, t_minishell *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->infile, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	ms->last_exit_status = 1;
}

void	ft_permission_denied_single_cmd(t_lcmd *cmd, t_minishell *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->outfile, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	ms->last_exit_status = 1;
}

void	ft_open_files_single_cmd(t_lcmd *cmd, t_minishell *ms)
{
	if (cmd->infile != NULL && cmd->fd_read == 0)
	{
		cmd->fd_read = open(cmd->infile, O_RDONLY, 0644);
		if (cmd->fd_read < 0)
			ft_open_failed_single_cmd(cmd, ms);
	}
	if (cmd->outfile != NULL && cmd->append == 1 && ms->last_exit_status != 1)
	{
		cmd->fd_write = open(cmd->outfile, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (cmd->fd_write == -1)
			ft_permission_denied_single_cmd(cmd, ms);
	}
	else if (cmd->outfile != NULL && ms->last_exit_status != 1)
	{
		cmd->fd_write = open(cmd->outfile, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (cmd->fd_write == -1)
			ft_permission_denied_single_cmd(cmd, ms);
	}
	if (cmd->infile == NULL)
		cmd->fd_read = 0;
	if (cmd->outfile == NULL)
		cmd->fd_write = 1;
}
