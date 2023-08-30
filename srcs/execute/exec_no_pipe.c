/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 20:18:03 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_exec_no_pipe(t_minishell *ms, char **env_tab)
{
	char	*cmd_with_path;
	pid_t	pid;
	int		exit_status;

	pid = improved_fork();
	if (pid < 0)
		return (perror("Fork"));
	if (pid == 0)
	{
		sub_dup2(ms->cmd->fd_read, ms->cmd->fd_write);
		if (ft_get_path_line(ms) == NULL)
			ft_path_failed(ms->cmd->cmd);
		cmd_with_path = ft_get_right_path(ms->cmd->cmd, ms);
		if (cmd_with_path == NULL)
			exit(127);
		if (execve(cmd_with_path, ms->cmd->option, env_tab) < 0)
		{
			ft_path_failed(ms->cmd->cmd);
			free(cmd_with_path);
			exit(127);
		}
	}
	else if (pid > 0)
		parent_exec_no_pipe(&pid, &exit_status, ms);
}

void	parent_exec_no_pipe(pid_t *pid, int *exit_status, t_minishell *ms)
{
	waitpid(*pid, exit_status, 0);
	if (pid)
	{
		if (WIFEXITED(*exit_status))
		{
			ms->last_exit_status = WEXITSTATUS(*exit_status);
		}
		else if (ms->last_exit_status == 0)
		{
			if (ft_strncmp(ms->cmd->cmd, "top", 3) == 0
				&& ft_strlen(ms->cmd->cmd) == 3)
				ms->last_exit_status = 0;
			else
			{
				ms->last_exit_status = g_status;
			}
		}
	}
}

void	ft_exec_no_pipe(t_minishell *ms, char **envp)
{
	if (ms->cmd != NULL && ms->last_exit_status == 0)
	{
		ft_open_files_single_cmd(ms->cmd, ms);
		if ((builtin_check(ms->cmd->cmd)) == 1)
		{
			if (ms->cmd->fd_read < 0 || ms->cmd->fd_write < 0)
				return ;
			builtin_run(ms, ms->cmd);
		}
		else
		{
			if (ms->cmd->fd_read < 0 || ms->cmd->fd_write < 0)
				return ;
			child_exec_no_pipe(ms, envp);
		}
	}
}
