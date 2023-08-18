/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/18 15:49:28 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern g_global	global;

void	ft_set_fd(t_pipex *p, t_lcmd *node)
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
}

int	ft_exec_child(t_lcmd *cmd, char **envp, t_minishell *ms)
{
	char	*cmd_with_path;

	cmd_with_path = ft_get_right_path(cmd->cmd, ms);
	if (!cmd_with_path)
	{
		exit(127);
	}
	if (execve(cmd_with_path, cmd->option, envp) < 0)
	{
		free(cmd_with_path);
		exit(127);
	}
	return (0);
}

void	ft_parent_close(t_minishell *ms)
{
	close(ms->p->pipe_fd[(ms->p->idx + 1) % 2][0]);
	close(ms->p->pipe_fd[(ms->p->idx + 1) % 2][1]);
}

void	ft_exec_parent(t_minishell *ms, char *cmd, pid_t *pid)
{
	int	exit_status;

	if (ms->p->idx != 0)
		ft_parent_close(ms);
	waitpid(*pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		ms->last_exit_status = WEXITSTATUS(exit_status);
	else
	{
		if (ft_strncmp(cmd, "top", 3) == 0)
			ms->last_exit_status = 0;
		else
			ms->last_exit_status = global.status;
	}
}

void	ft_pipeline_execution(t_minishell *ms, char **envp)
{
	t_lcmd	*cmd;
	pid_t	pid;

	ft_init_pipes_struct(ms);
	cmd = ms->cmd;
	while (cmd != NULL)
	{
		ft_pipe_dep_mod(ms->p);
		pid = fork();
		if (pid == 0)
		{
			ft_set_fd(ms->p, cmd);
			if (builtin_check(cmd->cmd) == 1)
			{
				builtin_run(ms, cmd);
				exit(ms->last_exit_status);
			}
			else
				ft_exec_child(cmd, envp, ms);
		}
		if (pid > 0)
			ft_exec_parent(ms, cmd->cmd, &pid);
		ms->p->idx++;
		cmd = cmd->next;
	}
	waitpid(-1, NULL, 0);
}
