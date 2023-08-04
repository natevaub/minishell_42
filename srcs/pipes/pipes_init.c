/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/04 19:20:07 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipex_struct(t_minishell *ms)
{

	ms->p->count_cmds = total_len_cmd(ms->cmd);
	// printf("total len cmd: %d\n", ms->p->count_cmds);

	ms->p->idx = 0;

	print_list_fds(ms->cmd);
}



//set command list & read/write fds
void	set_pipe_fds(t_lcmd *cmd, int fd[2][2], t_minishell *ms)
{
	// t_lcmd	*list;
	// int		i;

	// i = -1;
	// list = ms->cmd;
	// // printf("fd[0][0]: %d\nfd[0][1]: %d\nfd[1][0]: %d\nfd[1][1]: %d\n", ms->p->pipe_fd[0][0], ms->p->pipe_fd[0][1], ms->p->pipe_fd[1][0], ms->p->pipe_fd[1][1]);
	// while (list && ++i < ms->p->count_cmds)
	// {
		if (ms->p->idx == 0)
			cmd->fd_read = cmd->fd_read;
		else if (ms->p->idx % 2 != 0)
		{
			cmd->fd_read = fd[0][0];
			close (fd[0][1]);
		}
		else
		{
			cmd->fd_read = fd[1][0];
			close (fd[1][1]);
		}
		dup2(cmd->fd_read, STDIN_FILENO);
		if (ms->p->idx == ms->p->count_cmds - 1)
			cmd->fd_write = cmd->fd_write;
		else if ((ms->p->idx % 2 == 0 || ms->p->idx == 0))
		{
			cmd->fd_write = fd[0][1];
			close (fd[0][0]);
		}
		else
		{
			cmd->fd_write = fd[1][1];
			close (fd[1][0]);
		}
		dup2(cmd->fd_read, STDIN_FILENO);
	// 	list = list->next;
	// }
}
