// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipes_init.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
// /*   Updated: 2023/08/07 12:07:19 by nvaubien         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// void	init_pipex_struct(t_minishell *ms)
// {

// 	ms->p->count_cmds = total_len_cmd(ms->cmd);
// 	// printf("total len cmd: %d\n", ms->p->count_cmds);

// 	ms->p->idx = 0;

// 	print_list_fds(ms->cmd);
// }

// int	dup_for_pipe(int *fd_rw, int in_out, int *to_close)
// {
// 	close(*to_close);
// 	if (dup2(*fd_rw, in_out) < 0)
// 	{
// 		return (-1);
// 	}
// 	close (*fd_rw);
// 	return (0);
// }


// void	set_pipe_fds(t_lcmd *cmd, int fd[2][2], int idx)
// {
// 		if (idx == 0)
// 		{
// 			if (dup2(cmd->fd_read, STDIN_FILENO) < 0)
// 			{
// 				perror("Dup2 stdin: ");
// 				global.last_exit_status = 1;
// 			}
// 		}
// 		else if (idx % 2 == 0)
// 		{
// 			dup_for_pipe(&fd[1][0], STDIN_FILENO, &fd[1][1]);
// 			// cmd->fd_read = fd[1][0];
// 			// close (fd[1][1]);
// 		}
// 		else
// 		{
// 			dup_for_pipe(&fd[0][0], STDIN_FILENO, &fd[0][1]);
// 			// cmd->fd_read = fd[0][0];
// 			// close (fd[0][1]);
// 		}
// 		printf("In dup2, after read\n");
// 		if (cmd->next == NULL)
// 		{
// 			if (dup2(cmd->fd_write, STDOUT_FILENO) < 0)
// 			{
// 				perror("Dup2 stdout: ");
// 				global.last_exit_status = 1;
// 			}
// 		}
// 		else if ((idx % 2 == 0 || idx == 0))
// 		{
// 			dup_for_pipe(&fd[0][1], STDOUT_FILENO, &fd[0][0]);
// 			// cmd->fd_write = fd[0][1];
// 			// close (fd[0][0]);
// 		}
// 		else
// 		{
// 			dup_for_pipe(&fd[1][1], STDOUT_FILENO, &fd[1][0]);
// 			// cmd->fd_write = fd[1][1];
// 			// close (fd[1][0]);
// 		}
// 		printf("In dup2, after write\n");
// }


// // if (ms->p->idx == 0)
// // 			cmd->fd_read = cmd->fd_read;
// // 		else if (ms->p->idx % 2 == 0)
// // 		{
// // 			cmd->fd_read = fd[1][0];
// // 			close (fd[1][1]);
// // 		}
// // 		else
// // 		{
// // 			cmd->fd_read = fd[0][0];
// // 			close (fd[0][1]);
// // 		}
// // 		dup2(cmd->fd_read, STDIN_FILENO);
// // 		if (ms->p->idx == ms->p->count_cmds - 1)
// // 			cmd->fd_write = cmd->fd_write;
// // 		else if ((ms->p->idx % 2 == 0 || ms->p->idx == 0))
// // 		{
// // 			cmd->fd_write = fd[0][1];
// // 			close (fd[0][0]);
// // 		}
// // 		else
// // 		{
// // 			cmd->fd_write = fd[1][1];
// // 			close (fd[1][0]);
// // 		}
// // 		dup2(cmd->fd_write, STDOUT_FILENO);

