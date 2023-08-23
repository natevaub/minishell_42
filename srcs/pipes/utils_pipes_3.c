/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/23 11:29:34 by ckarl            ###   ########.fr       */
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
	// g_status = 0;
}

void	ft_parent_close(t_minishell *ms)
{
	if (ms->p->idx != 0)
	{
		close(ms->p->pipe_fd[(ms->p->idx + 1) % 2][0]);
		close(ms->p->pipe_fd[(ms->p->idx + 1) % 2][1]);
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
