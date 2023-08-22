/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/22 16:58:01 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sub_dup2(int read, int write)
{
	if (read != 0)
	{
		if (improved_dup2(read, STDIN_FILENO) < 0)
		{
			exit(1);
		}
	}
	if (write != 1)
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
<<<<<<< HEAD

void	ft_init_pipes_struct(t_minishell *shell)
{
	shell->p = malloc(sizeof(t_pipex));
	if (!shell->p)
		exit(1);
	shell->p->count_cmds = ft_count_cmds(shell->cmd);
	shell->p->idx = 0;
	g_status = 0;
}
=======
>>>>>>> 6446f01d8b15cddf622c3a70a205460fa72c14a8
