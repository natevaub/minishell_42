/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/22 16:19:34 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

/*
	heredoc:
*/

//pipes are detected, parsing redirects tokens to this function
int	pipe_exec(t_minishell *ms)
{
	ms->p = malloc(sizeof(t_pipex));
	if (!ms->p)
		return (-1);																	//set errno
	init_pipex_struct(ms);
	while (ms->p->idx < ms->p->count_cmds)
	{
		child_exec(ms);
		ms->p->idx++;
	}
	final_free_and_close(ms);								//need to check if first close, waitpid, then free or if okay like this
	exit(0);													//necessary here??
	return (0);
}

//function creating fork for child & executing command
void	child_exec(t_minishell *ms)
{
	char	*cmd_with_path;
	t_lcmd	*to_do;
	char	**env_pipe;
	pid_t	pid;

	pid = improved_fork();
	env_pipe = env_list_to_env_tab();
	to_do = get_node_pipes(ms->cmd, ms->p->idx);
	if (pid < 0)
		return (perror("Fork"));
	if (pid == 0)
	{
		// printf("list fd read: %d and write %d, p->idx: %d\n", to_do->fd_read, to_do->fd_write, p->idx);
		sub_dup2(to_do->fd_read, to_do->fd_write);
		close_pipes(ms->p);
		cmd_with_path = get_right_path(to_do->cmd);
		if (!cmd_with_path)
		{
			// msg(ERR_CMD);													//set error msg
			free_two_dimension_array(env_pipe);
			exit(1);
		}
		if ((builtin_check(ms->cmd->cmd)) == 1)
			builtin_redirect(ms);
		else if (execve(cmd_with_path, to_do->option, env_pipe) < 0)
		{
			free_two_dimension_array(env_pipe);
			return (perror(ERR_EXEC "(parent)"));
		}
		free_two_dimension_array(env_pipe);
	}
}
