/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/07 16:41:31 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

int	ft_set_fd(t_minishell *shell, t_pipex *p)
{
	if (p->idx == 0)
	{
		close(p->pipe_fd[0][0]);
		dup2(p->pipe_fd[0][1], STDOUT_FILENO);
	}
	else if (p->idx != p->count_cmds - 1)
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);  // Close write end of previous pipe
		dup2(p->pipe_fd[(p->idx) - 1 % 2][0], STDIN_FILENO); // Set input from pipe
		close(p->pipe_fd[(p->idx) % 2][0]);
		dup2(p->pipe_fd[(p->idx) % 2][1], STDOUT_FILENO);
	}
	else
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);
		dup2(p->pipe_fd[(p->idx - 1) % 2][0], STDIN_FILENO);
	}
	// close(p->pipe_fd[p->idx % 2][0]);				deplacé de apres ft_set_fds
	// close(p->pipe_fd[p->idx % 2][1]);
	return (0);
}

int	ft_exec_child(t_lcmd *cmd, char **envp)
{
	char	*cmd_with_path;
	cmd_with_path = ft_get_right_path(cmd->cmd);
	if (execve(cmd_with_path, cmd->option, envp) < 0)
	{
		printf("Ca n'a pas marcher\n");
		free(cmd_with_path);
		exit(1);
		return (1);
	}
	return (0);
}

void	ft_exec_parent(t_pipex *p, pid_t *pid)
{
	int	i;
	int	status;

	i = -1;
	close(p->pipe_fd[(p->idx - 1) % 2][0]);
	close(p->pipe_fd[(p->idx - 1) % 2][1]);
	close(p->pipe_fd[(p->idx) % 2][0]);
	close(p->pipe_fd[(p->idx) % 2][1]);
	while (++i < p->count_cmds)
	{
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit: 3\n", 8);
			else if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			global.last_exit_status = 128 + status;
		}
		if (WIFEXITED(status))
			global.last_exit_status = WEXITSTATUS(status);
	}
}

int	ft_pipeline_execution(t_minishell *shell, char **envp)
{
	t_lcmd	*cmd;
	t_pipex	*p;
	pid_t	pid;

	p = malloc(sizeof(t_pipex));
	ft_init_pipes_struct(shell, p);
	cmd = shell->cmd;
	while (cmd != NULL)
	{
		ft_pipe_dep_mod(p);
		pid = fork();
		if (pid == 0)
		{
			ft_set_fd(shell, p);
			ft_exec_child(cmd, envp);
		}
		else if (pid > 0)
		{
			if (p->idx != 0)
			{
				close(p->pipe_fd[(p->idx - 1) % 2][0]);
				close(p->pipe_fd[(p->idx - 1) % 2][1]);
			}
		}
		p->idx++;
		cmd = cmd->next;
	}
	ft_exec_parent(p, &pid);
	return (0);
}

		// close(p->pipe_fd[(p->idx - 1) % 2][0]);
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);