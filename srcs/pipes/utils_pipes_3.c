/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 17:44:35 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_pipes_struct(t_minishell *shell)
{
	shell->p = malloc(sizeof(t_pipex));
	if (!shell->p)
		exit(1);
	shell->p->count_cmds = ft_count_cmds(shell->cmd);
	shell->p->idx = 0;
}

void	ft_parent_close(t_minishell *ms)
{
	if (ms->p->idx != 0)
	{
		close(ms->p->pipe_fd[(ms->p->idx - 1) % 2][0]);
		close(ms->p->pipe_fd[(ms->p->idx - 1) % 2][1]);
	}
}

int	ft_pipe_dep_mod(t_pipex *p)
{
	if (p->idx % 2 == 0)
	{
		pipe(p->pipe_fd[0]);
	}
	else
	{
		pipe(p->pipe_fd[1]);
	}
	return (0);
}

void	ft_path_failed(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

void	ft_open_files(t_lcmd *cmd, t_minishell *ms)
{
	if (cmd->infile != NULL && cmd->fd_read == 0)
	{
		cmd->fd_read = open(cmd->infile, O_RDONLY, 0644);
		if (cmd->fd_read < 0)
			ft_open_failed(cmd, ms);
	}
	if (cmd->outfile != NULL && cmd->append == 1)
	{
		cmd->fd_write = open(cmd->outfile, O_CREAT | O_APPEND | O_RDWR, 0666);
		if (cmd->fd_write == -1)
			ft_permission_denied(cmd, ms);
	}
	else if (cmd->outfile != NULL)
	{
		cmd->fd_write = open(cmd->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (cmd->fd_write == -1)
			ft_permission_denied(cmd, ms);
	}
	if (cmd->infile == NULL)
		cmd->fd_read = 0;
	if (cmd->outfile == NULL)
		cmd->fd_write = 1;
}
