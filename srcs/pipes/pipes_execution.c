// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipes_execution.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
// /*   Updated: 2023/08/07 12:17:59 by nvaubien         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// extern t_global	global;

// //pipes are detected, parsing redirects tokens to this function

// // int exec_pipe(t_minishell *ms, char **envp)
// // {
// // 	t_lcmd	*curr;
// // 	pid_t	pid;
// // 	int		exit_status;
// // 	int		children;

// // 	children = 0;
// // 	ms->p = malloc(sizeof(t_pipex));
// // 	if (!ms->p)
// // 		return (1);																	//set errno
// // 	init_pipex_struct(ms);
// // 	while (ms->p->idx < ms->p->count_cmds && children < ms->p->count_cmds)
// // 	{
// // 		curr = get_node_lcmd(ms->cmd, ms->p->idx);
// // 		printf("cmd: %s & idx: %d \n", curr->cmd, ms->p->idx);
// // 		pid = improved_fork();
// // 		if (pid == 0)
// // 		{
// // 			run_cmd(curr, ms, envp);
// // 		}
// // 		else if (pid > 0)
// // 			children++;
// // 		ms->p->idx++;
// // 	}
// // 	// close_pipes(ms);
// // 	close(ms->p->pipe_fd[0][1]);
// // 	close(ms->p->pipe_fd[1][0]);
// // 	close(ms->p->pipe_fd[0][0]);
// // 	close(ms->p->pipe_fd[1][1]);
// // 	while (waitpid(-1, &exit_status, 0) > 0)
// // 		;
// // 	if (WIFEXITED(exit_status))
// // 		global.last_exit_status = WEXITSTATUS(exit_status);

// // 	return (global.last_exit_status);																//exits the program, why?
// // }

// // void	run_cmd(t_lcmd *cmd, t_minishell *ms, char **envp)
// // {
// // 	if (builtin_check(cmd->cmd) != 1)
// // 	{
// // 		child_exec(cmd, envp, ms);
// // 	}
// // 	else
// // 		builtin_redirect(cmd);
// // }

// //function creating fork for child & executing command
// // void	child_exec(t_lcmd *cmd, char **envp, t_minishell *ms)
// // {
// // 	char	*cmd_with_path;

// // 		printf("before execve in child exec\n");
// // 		sub_dup2(cmd->fd_read, cmd->fd_write);
// // 		close_pipes(ms);
// // 		cmd_with_path = get_right_path(cmd->cmd);
// // 		if (!cmd_with_path)
// // 		{
// // 			global.last_exit_status = 1;
// // 		}
// // 		if (execve(cmd_with_path, cmd->option, envp) < 0)
// // 		{
// // 			free(cmd_with_path);
// // 			return (perror("Execve"));
// // 		}
// // }

// int exec_pipe(t_minishell *ms, char **envp)
// {
// 	t_lcmd	*curr;
// 	pid_t	pid;
// 	int		exit_status;
// 	int		fd[2][2];

// 	ms->p = malloc(sizeof(t_pipex));
// 	if (!ms->p)
// 		return (1);													//set errno
// 	init_pipex_struct(ms);
// 	curr = ms->cmd;
// 	pipe(fd[0]);
// 	pipe(fd[1]);
// 	while (ms->p->idx < ms->p->count_cmds && curr)
// 	{
// 		printf("cmd: %s & idx: %d \n", curr->cmd, ms->p->idx);
// 		pid = fork();
// 		if (pid < 0)
// 			printf("ERROR fork\n");
// 		if (pid == 0)
// 		{
// 			run_cmd(curr, ms, envp, fd);
// 		}

// 		curr = curr->next;
// 		ms->p->idx++;
// 	}
// 	close(fd[0][0]);
// 	close(fd[1][1]);
// 	close(fd[0][1]);
// 	close(fd[1][0]);
// 	while (waitpid(-1, &exit_status, 0) > 0)
// 		;
// 	if (WIFEXITED(exit_status))
// 		global.last_exit_status = WEXITSTATUS(exit_status);

// 	printf("before waitpid\n");

// 	free(ms->p);
// 	return (global.last_exit_status);
// }

// void	run_cmd(t_lcmd *cmd, t_minishell *ms, char **envp, int fd[2][2])
// {
// 	if (builtin_check(cmd->cmd) != 1)
// 	{
// 		child_exec(cmd, envp, ms, fd);
// 	}
// 	else
// 	{
// 		builtin_redirect(cmd);
// 	}
// }

// //function creating fork for child & executing command
// void	child_exec(t_lcmd *cmd, char **envp, t_minishell *ms, int fd[2][2])
// {
// 	char	*cmd_with_path;

// 	printf("child: idx: %d\n", ms->p->idx);
// 	set_pipe_fds(cmd, fd, ms->p->idx);
// 	cmd_with_path = get_right_path(cmd->cmd);
// 	printf("cmd path: %s", cmd_with_path);
// 	if (!cmd_with_path)
// 	{
// 		global.last_exit_status = 1;
// 	}
// 	if (execve(cmd_with_path, cmd->option, envp) < 0)
// 	{
// 		free(cmd_with_path);
// 		return (perror("Execve"));
// 	}
// }

// 	// if (ms->p->idx > 0)
// 	// {
// 	// 	// Close the write end of the first pipe (for all children except the first)
// 	// 	close(fd[0][1]);
// 	// 	// Duplicate the read end of the first pipe to STDIN (for all children except the first)
// 	// 	dup2(fd[0][0], STDIN_FILENO);
// 	// 	// Close the read end of the first pipe (for all children except the first)
// 	// 	close(fd[0][0]);
// 	// }
// 	// printf("between the file closings\n");
// 	// if (ms->p->idx < (ms->p->count_cmds - 1))
// 	// {
// 	// 	// Close the read end of the second pipe (for all children except the last)
// 	// 	close(fd[1][0]);
// 	// 	// Duplicate the write end of the second pipe to STDOUT (for all children except the last)
// 	// 	dup2(fd[1][1], STDOUT_FILENO);
// 	// 	// Close the write end of the second pipe (for all children except the last)
// 	// 	close(fd[1][1]);
// 	// }
// 	// printf("after the file closings\n");

