/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/22 16:31:20 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipex_struct(t_minishell *ms)
{
	pipe(ms->p->pipe_fd[0]);
	pipe(ms->p->pipe_fd[1]);
	ms->p->count_cmds = total_len_cmd(ms->cmd);
	// printf("total len cmd: %d\n", ms->p->count_cmds);
	ms->p->idx = 0;
	set_pipe_fds(ms);
	print_list_fds(ms->cmd);
}

//set command list & read/write fds
void	set_pipe_fds(t_minishell *ms)
{
	t_lcmd	*list;
	int		i;

	i = -1;
	list = ms->cmd;
	// printf("fd[0][0]: %d\nfd[0][1]: %d\nfd[1][0]: %d\nfd[1][1]: %d\n", ms->p->pipe_fd[0][0], ms->p->pipe_fd[0][1], ms->p->pipe_fd[1][0], ms->p->pipe_fd[1][1]);
	while (list && ++i < ms->p->count_cmds)
	{
		if (i == 0)
			list->fd_read = list->fd_read;
		else if (i % 2 != 0)
			list->fd_read = ms->p->pipe_fd[0][0];
		else
			list->fd_read = ms->p->pipe_fd[1][0];
		if (i == ms->p->count_cmds - 1)
			list->fd_write = list->fd_write;
		else if ((i % 2 == 0 || i == 0))
			list->fd_write = ms->p->pipe_fd[0][1];
		else
			list->fd_write = ms->p->pipe_fd[1][1];
		list = list->next;
	}
}
