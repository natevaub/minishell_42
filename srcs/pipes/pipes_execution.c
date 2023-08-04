/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/04 12:43:03 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

/*
	heredoc:
*/

//pipes are detected, parsing redirects tokens to this function
int exec_pipe(t_minishell *ms, char **envp)
{
	t_lcmd	*curr;
	pid_t	pid;
	int		exit_status;
	int			pipe_fd[2][2];


	ms->p = malloc(sizeof(t_pipex));
	if (!ms->p)
		return (1);																	//set errno
	pipe(pipe_fd[0]);
	pipe(pipe_fd[1]);
	set_pipe_fds(ms);
	init_pipex_struct(ms);
	curr = ms->cmd;
		// printf("first command: %s\n", ms->cmd->cmd);
	printf("count_cmds: %d\n", ms->p->count_cmds);
	while (curr)
	{
		// curr = get_node_lcmd(ms->cmd, ms->p->idx);
		printf("cmd: %s & idx: %d \n", curr->cmd, ms->p->idx);
		pid = improved_fork();
		if (pid == 0)
		{
			run_cmd(curr, ms->p, envp);
		}
		ms->p->idx++;
		curr = curr->next;
	}
	close_pipes(ms->p);
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	if (WIFEXITED(exit_status))
		global.last_exit_status = WEXITSTATUS(exit_status);

	return (global.last_exit_status);																//exits the program, why?
}

void	run_cmd(t_lcmd *cmd, t_pipex *p, char **envp)
{
	if (builtin_check(cmd->cmd) != 1)
	{
		child_exec(cmd, envp, p);
	}
	builtin_redirect(cmd);
}

//function creating fork for child & executing command
void	child_exec(t_lcmd *cmd, char **envp, t_pipex *p)
{
	char	*cmd_with_path;

		printf("before execve in child exec\n");
		sub_dup2(cmd->fd_read, cmd->fd_write);
		close_pipes(p);
		cmd_with_path = get_right_path(cmd->cmd);
		if (!cmd_with_path)
		{
			global.last_exit_status = 1;
		}
		if (execve(cmd_with_path, cmd->option, envp) < 0)
		{
			free(cmd_with_path);
			return (perror("Execve"));
		}
}
