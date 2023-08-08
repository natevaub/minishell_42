/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/08 10:32:50 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

int	ft_set_fd(t_minishell *shell, t_pipex *p, t_lcmd *node)
{
	if (p->idx == 0)
	{
		if (node->fd_read != 0)
		{
			dup2(node->fd_read, STDIN_FILENO);
			close(node->fd_read);
		}
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
		if (node->fd_write != 1)
		{
			dup2(node->fd_write, STDOUT_FILENO);
			close(node->fd_write);
		}
		close(p->pipe_fd[(p->idx - 1) % 2][1]);
		dup2(p->pipe_fd[(p->idx - 1) % 2][0], STDIN_FILENO);
	}
	// close(p->pipe_fd[p->idx % 2][0]);				deplacé de apres ft_set_fds
	// close(p->pipe_fd[p->idx % 2][1]);
	return (0);
}

int	ft_set_fd_builtins(t_minishell *shell, t_pipex *p, t_lcmd *node)
{
	// Handle input redirection if needed
	if (node->fd_read != 0)
	{
		dup2(node->fd_read, STDIN_FILENO);
		close(node->fd_read);
	}
	
	// Handle output redirection if needed
	if (node->fd_write != 1)
	{
		dup2(node->fd_write, STDOUT_FILENO);
		close(node->fd_write);
	}

	return (0);
}

int	ft_exec_child(t_lcmd *cmd, char **envp)
{
	char	*cmd_with_path;
	cmd_with_path = ft_get_right_path(cmd->cmd);
	if (execve(cmd_with_path, cmd->option, envp) < 0)
	{
		free(cmd_with_path);
		exit(1);
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
	pid_t	pid;

	ft_init_pipes_struct(shell);
	cmd = shell->cmd;
	while (cmd != NULL)
	{
		ft_pipe_dep_mod(shell->p);
		// if (builtin_check(cmd->cmd) == 1)
		// {
		// 	ft_set_fd_builtins(shell, shell->p, cmd);
		// 	builtin_redirect(cmd);
		// }
		pid = fork();
		if (pid == 0)
		{
			ft_set_fd(shell, shell->p, cmd);
			ft_exec_child(cmd, envp);
		}
		else if (pid > 0)
		{
			if (shell->p->idx != 0)
			{
				close(shell->p->pipe_fd[(shell->p->idx - 1) % 2][0]);
				close(shell->p->pipe_fd[(shell->p->idx - 1) % 2][1]);
			}
		}
		shell->p->idx++;
		cmd = cmd->next;
	}
	ft_exec_parent(shell->p, &pid);
	return (0);
}

		// close(p->pipe_fd[(p->idx - 1) % 2][0]);
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);
		// close(p->pipe_fd[(p->idx - 1) % 2][1]);
