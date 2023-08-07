/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:10:31 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/07 12:07:53 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//print error text & return to main
// int	error(char *str)
// {
// 	perror(str);
// 	return (-1);
// }

// void	close_pipes(t_minishell *ms)
// {
// 	if (ms->p->idx == 0)
// 	{
// 		close(ms->p->pipe_fd[0][0]);
// 		close(ms->p->pipe_fd[1][1]);
// 		close(ms->p->pipe_fd[1][0]);
// 		// if (ms->cmd->fd_read != STDIN_FILENO)
// 		// 	close(ms->cmd->fd_read);
// 	}
// 	else if (ms->p->idx == ms->p->count_cmds - 1)
// 	{
// 		if (ms->p->idx % 2 == 0)
// 			close(ms->p->pipe_fd[1][0]);
// 		else
// 			close(ms->p->pipe_fd[0][0]);
// 		close(ms->p->pipe_fd[1][1]);
// 		close(ms->p->pipe_fd[0][1]);
		// if (ms->cmd->fd_write != STDOUT_FILENO)
		// 	close(ms->cmd->fd_write);
// 	}
// 	else if (ms->p->idx % 2 == 0 && ms->p->idx != 0)
// 	{
// 		close(ms->p->pipe_fd[0][1]);
// 		close(ms->p->pipe_fd[1][0]);
// 	}
// 	else if (ms->p->idx % 2 != 0)
// 	{
// 		close(ms->p->pipe_fd[0][0]);
// 		close(ms->p->pipe_fd[1][1]);
// 	}
// }

// void	final_free_and_close(t_minishell *ms)
// {
// 	// close(ms->infile_fd);
// 	// close(ms->outfile_fd);
// 	close_pipes(ms->p);
// 	waitpid(-1, NULL, 0);
// 	// while (ms->cmd)
// 	// {
// 	// 	free(ms->cmd->cmd);
// 	// 	free_two_dimension_array(pipex->commands->option);
// 	// 	pipex->commands = pipex->commands->next;
// 	// }
// }