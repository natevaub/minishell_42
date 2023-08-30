/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 16:11:04 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sub_dup2(int read, int write)
{
	if (read > 0)
	{
		if (improved_dup2(read, STDIN_FILENO) < 0)
		{
			exit(1);
		}
	}
	if (write > 1)
	{
		if (improved_dup2(write, STDOUT_FILENO) < 0)
		{
			exit(1);
		}
	}
}

int	improved_dup2(int fildes, int fildes2)
{
	int	error;

	error = dup2(fildes, fildes2);
	if (error < 0)
	{
		perror("error dup2");
	}
	return (error);
}

int	improved_pipe(int fd[2])
{
	int	error;

	error = pipe(fd);
	if (error == -1)
	{
		perror("error pipe");
		exit(1);
	}
	return (error);
}

pid_t	improved_fork(void)
{
	pid_t	error;

	error = fork();
	if (error == -1)
	{
		perror("error fork");
		exit(1);
	}
	return (error);
}

void	close_all_fds(t_minishell *ms)
{
	t_lcmd	*head;

	head = ms->cmd;
	while (head)
	{
		if (head->fd_read != 0)
			close(head->fd_read);
		if (head->fd_write != 1)
			close(head->fd_write);
		head = head->next;
	}
}
