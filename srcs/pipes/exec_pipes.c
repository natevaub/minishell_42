/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 17:44:41 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set_fd(t_pipex *p, t_lcmd *node)
{
	if (p->idx != p->count_cmds - 1)
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);
		close(p->pipe_fd[(p->idx) % 2][0]);
		if (node->fd_write > 1)
			improved_dup2(node->fd_write, STDOUT_FILENO);
		else
			improved_dup2(p->pipe_fd[(p->idx) % 2][1], STDOUT_FILENO);
		if (node->fd_read > 0)
			improved_dup2(node->fd_read, STDIN_FILENO);
		else
			improved_dup2(p->pipe_fd[(p->idx - 1) % 2][0], STDIN_FILENO);
	}
	else
	{
		close(p->pipe_fd[(p->idx - 1) % 2][1]);
		improved_dup2(node->fd_write, STDOUT_FILENO);
		if (node->fd_read > 0)
			improved_dup2(node->fd_read, STDIN_FILENO);
		else
			improved_dup2(p->pipe_fd[(p->idx - 1) % 2][0], STDIN_FILENO);
	}
}

int	ft_exec_child(t_lcmd *cmd, char **envp, t_minishell *ms)
{
	char	*cmd_with_path;

	if (ft_get_path_line(ms) == NULL)
		ft_path_failed(ms->cmd->cmd);
	cmd_with_path = ft_get_right_path(cmd->cmd, ms);
	if (!cmd_with_path)
	{
		exit(127);
	}
	if (execve(cmd_with_path, cmd->option, envp) < 0)
	{
		ft_path_failed(cmd->cmd);
		free(cmd_with_path);
		exit(127);
	}
	return (0);
}

void	ft_exec_parent(t_minishell *ms, t_lcmd *cmd, pid_t *pid)
{
	int	i;
	int	exit_status;
	int	tmp;

	i = -1;
	if (ms->p->idx != 0)
		ft_parent_close(ms);
	close(ms->p->pipe_fd[(ms->p->idx) % 2][0]);
	close(ms->p->pipe_fd[(ms->p->idx) % 2][1]);
	while (++i < ms->p->count_cmds)
	{
		tmp = waitpid(-1, &exit_status, 0);
		if (pid && tmp == *pid)
		{
			if (WIFEXITED(exit_status))
			ms->last_exit_status = WEXITSTATUS(exit_status);
			else
			{
				if (cmd != NULL && ft_strncmp(cmd->cmd, "top", 3) == 0)
					ms->last_exit_status = 0;
				else
					ms->last_exit_status = g_status;
			}
		}
	}
}

void	ft_run_multiple_cmds(t_minishell *ms, char **envp, t_lcmd *cmd)
{
	if (builtin_check(cmd->cmd) == 1)
	{
		builtin_run(ms, cmd);
		exit(ms->last_exit_status);
	}
	else
		ft_exec_child(cmd, envp, ms);
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
			ft_open_files(cmd, ms);
			if (ms->p->idx == 0)
				ft_set_fd_first(ms->p, cmd);
			else
				ft_set_fd(ms->p, cmd);
			ft_run_multiple_cmds(ms, envp, cmd);
		}
		if (pid > 0)
			ft_parent_close(ms);
		ms->p->idx++;
		cmd = cmd->next;
	}
	close_all_fds(ms);
	ft_exec_parent(ms, cmd, &pid);
}
