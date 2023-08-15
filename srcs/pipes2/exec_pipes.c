/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/15 18:32:55 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern g_global	global;

int	ft_set_fd(t_pipex *p, t_lcmd *node)
{
	if (p->idx == 0)
	{
		close(p->pipe_fd[0][0]);
		sub_dup2(node->fd_read, p->pipe_fd[0][1]);
		if (node->fd_read != 0)
			close(node->fd_read);
	}
	else if (p->idx != p->count_cmds - 1)
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);
		close(p->pipe_fd[(p->idx) % 2][0]);
		sub_dup2(p->pipe_fd[(p->idx - 1) % 2][0], p->pipe_fd[(p->idx) % 2][1]);
	}
	else
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);
		sub_dup2(p->pipe_fd[(p->idx - 1) % 2][0], node->fd_write);
		if (node->fd_write != 1)
			close(node->fd_write);
	}
	return (0);
}

int	ft_exec_child(t_lcmd *cmd, char **envp, t_minishell *ms)
{
	char	*cmd_with_path;

	cmd_with_path = ft_get_right_path(cmd->cmd, ms);
	if (execve(cmd_with_path, cmd->option, envp) < 0)
	{
		free(cmd_with_path);
		exit(127);
	}
	return (0);
}

void	ft_exec_parent(t_minishell *ms, pid_t *pid)
{
	int	i;
	int	status;

	i = -1;
	close(ms->p->pipe_fd[(ms->p->idx - 1) % 2][0]);
	close(ms->p->pipe_fd[(ms->p->idx - 1) % 2][1]);
	close(ms->p->pipe_fd[(ms->p->idx) % 2][0]);
	close(ms->p->pipe_fd[(ms->p->idx) % 2][1]);
	while (++i < ms->p->count_cmds)
	{
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit: 3\n", 8);
			else if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			ms->last_exit_status = 128 + status;
		}
		if (WIFEXITED(status))
			ms->last_exit_status = WEXITSTATUS(status);
	}
}

void	ft_exec_builtin(t_minishell *ms, t_lcmd *cmd)
{
	if (ms->p->idx == 0)
	{
		cmd->fd_write = ms->p->pipe_fd[0][1];
		// close(p->pipe_fd[0][0]);
		// sub_dup2(node->fd_read, p->pipe_fd[0][1]);
		// if (node->fd_read != 0)
		// 	close(node->fd_read);
	}
	else if (ms->p->idx != ms->p->count_cmds - 1)
	{
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);
		// close(p->pipe_fd[(p->idx) % 2][0]);
		// sub_dup2(p->pipe_fd[(p->idx - 1) % 2][0], p->pipe_fd[(p->idx) % 2][1]);
		cmd->fd_write = ms->p->pipe_fd[(ms->p->idx) % 2][1];
		cmd->fd_read = ms->p->pipe_fd[(ms->p->idx - 1) % 2][0];

	}
	else
	{
		cmd->fd_read = ms->p->pipe_fd[(ms->p->idx - 1) % 2][0];
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);
		// sub_dup2(p->pipe_fd[(p->idx - 1) % 2][0], node->fd_write);
		// if (node->fd_write != 1)
		// 	close(node->fd_write);
	}
	builtin_run(ms, cmd);
	exit(1);
}

int	ft_pipeline_execution(t_minishell *ms, char **envp)
{
	t_lcmd	*cmd;
	pid_t	pid;

	ft_init_pipes_struct(ms);
	cmd = ms->cmd;
	while (cmd != NULL)
	{
		ft_pipe_dep_mod(ms->p);
		// if (builtin_check(cmd->cmd) == 1)
		// {
		// 	pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		ft_set_fd(ms, ms->p, cmd);
		// 		builtin_redirect(ms, cmd);
		// 		exit(1);
		// 	}
		// } else {
			pid = fork();
			if (pid == 0)
			{
				ft_set_fd(ms->p, cmd);
				if (builtin_check(cmd->cmd) == 1)
				{
					ft_exec_builtin(ms, cmd);
					// builtin_run(ms, cmd);
					// exit(1);
				}
				else
					ft_exec_child(cmd, envp, ms);
			}

		// }
		else if (pid > 0)
		{
			if (ms->p->idx != 0)
			{
				close(ms->p->pipe_fd[(ms->p->idx - 1) % 2][0]);
				close(ms->p->pipe_fd[(ms->p->idx - 1) % 2][1]);
			}
		}
		ms->p->idx++;
		cmd = cmd->next;
	}
	ft_exec_parent(ms, &pid);
	return (0);
}

// int ft_set_fd_builtins(t_minishell *ms, t_pipex *p, t_lcmd *node)
// {
// 	// Handle input redirection if needed
// 	if (node->fd_read != 0)
// 	{
// 		dup2(node->fd_read, STDIN_FILENO);
// 		close(node->fd_read);
// 	}

// 	// Handle output redirection if needed
// 	if (node->fd_write != 1)
// 	{
// 		dup2(node->fd_write, STDOUT_FILENO);
// 		close(node->fd_write);
// 	}

// 	return (0);
// }

//first version of ft_set_fd
/*if (p->idx == 0)
	{
		close(p->pipe_fd[0][0]);
		sub_dup2(node->fd_read, p->pipe_fd[0][1]);
		// if (node->fd_read != 0)
		// {
		// 	dup2(node->fd_read, STDIN_FILENO);
		if (node->fd_read != 0)
			close(node->fd_read);
		// }

		// dup2(p->pipe_fd[0][1], STDOUT_FILENO);
	}
	else if (p->idx != p->count_cmds - 1)
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);  // Close write end of previous pipe
		// dup2(p->pipe_fd[(p->idx - 1) % 2][0], STDIN_FILENO); // Set input from pipe
		close(p->pipe_fd[(p->idx) % 2][0]);
		sub_dup2(p->pipe_fd[(p->idx - 1) % 2][0], p->pipe_fd[(p->idx) % 2][1]);
		// dup2(p->pipe_fd[(p->idx) % 2][1], STDOUT_FILENO);
	}
	else
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);
		sub_dup2(p->pipe_fd[(p->idx - 1) % 2][0], node->fd_write);
		if (node->fd_write != 1)
		{
		// 	dup2(node->fd_write, STDOUT_FILENO);
			close(node->fd_write);
		}

		// dup2(p->pipe_fd[(p->idx - 1) % 2][0], STDIN_FILENO);
	}*/