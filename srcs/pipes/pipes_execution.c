/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/04 20:09:55 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//pipes are detected, parsing redirects tokens to this function
int exec_pipe(t_minishell *ms, char **envp)
{
	t_lcmd	*curr;
	pid_t	pid;
	int		exit_status;
	int		fd[2][2];

	ms->p = malloc(sizeof(t_pipex));
	if (!ms->p)
		return (1);																	//set errno
	init_pipex_struct(ms);
	curr = ms->cmd;
	pipe(fd[0]);
	pipe(fd[1]);
	while (ms->p->idx < ms->p->count_cmds && curr)
	{
		printf("cmd: %s & idx: %d \n", curr->cmd, ms->p->idx);
		pid = fork();
		if (pid < 0)
			printf("ERROR fork\n");
		if (pid == 0)
		{
			run_cmd(curr, ms, envp, fd);											//doesn't follow right order for children, executes last command but pipes don't seem to be working
																					//I'm not using fd_read and fd_write but I'm using dup2 on the pipes directly
		}

		curr = curr->next;
		ms->p->idx++;
	}
	// close_pipes(ms);
	close(fd[0][0]);
	close(fd[1][1]);
	close(fd[0][1]);
	close(fd[1][0]);

	printf("before waitpid\n");
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	if (WIFEXITED(exit_status))
		global.last_exit_status = WEXITSTATUS(exit_status);

	free(ms->p);
	return (global.last_exit_status);
}

void	run_cmd(t_lcmd *cmd, t_minishell *ms, char **envp, int fd[2][2])
{
	if (builtin_check(cmd->cmd) != 1)
	{
		child_exec(cmd, envp, ms, fd);
	}
	else
	{
		builtin_redirect(cmd);
	}
}

//function creating fork for child & executing command
void	child_exec(t_lcmd *cmd, char **envp, t_minishell *ms, int fd[2][2])
{
	char	*cmd_with_path;

	printf("child: idx: %d\n", ms->p->idx);

	if (ms->p->idx > 0)
	{
		// Close the write end of the first pipe (for all children except the first)
		close(fd[0][1]);
		// Duplicate the read end of the first pipe to STDIN (for all children except the first)
		dup2(fd[0][0], STDIN_FILENO);
		// Close the read end of the first pipe (for all children except the first)
		close(fd[0][0]);
	}
	if (ms->p->idx < ms->p->count_cmds - 1)
	{
		// Close the read end of the second pipe (for all children except the last)
		close(fd[1][0]);
		// Duplicate the write end of the second pipe to STDOUT (for all children except the last)
		dup2(fd[1][1], STDOUT_FILENO);
		// Close the write end of the second pipe (for all children except the last)
		close(fd[1][1]);
	}
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
