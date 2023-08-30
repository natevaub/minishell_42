/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 17:44:56 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set_fd_first(t_pipex *p, t_lcmd *node)
{
	if (p->idx == 0)
	{
		close(p->pipe_fd[0][0]);
		improved_dup2(node->fd_read, STDIN_FILENO);
		if (node->fd_write > 1)
			improved_dup2(node->fd_write, STDOUT_FILENO);
		else
			improved_dup2(p->pipe_fd[0][1], STDOUT_FILENO);
	}
}
