/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:10:31 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/22 16:22:32 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//print error text & return to main
int	error(char *str)
{
	perror(str);
	return (-1);
}

//close all pipe ends except the one where we need to write to
void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe_fd[0][0]);
	close(pipex->pipe_fd[0][1]);
	close(pipex->pipe_fd[1][0]);
	close(pipex->pipe_fd[1][1]);
}

void	final_free_and_close(t_pipex *pipex)
{
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	close_pipes(pipex);
	waitpid(-1, NULL, 0);
	while (pipex->commands)
	{
		free(pipex->commands->cmd);
		free_two_dimension_array(pipex->commands->option);
		pipex->commands = pipex->commands->next;
	}
}