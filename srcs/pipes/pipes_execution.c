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
int	pipe_exec(int argc, char **argv)													//adjust parameters
{
	t_pipex	*p;

	p = malloc(sizeof(t_pipex));
	if (!p)
		return (-1);																	//set errno
	init_pipex_struct(argc, argv, p);
	while (p->idx < p->count_cmds)
	{
		child_exec(p);
		p->idx++;
	}
	final_free_and_close(p);								//need to check if first close, waitpid, then free or if okay like this
	exit(0);													//necessary here??
	return (0);
}

//function creating fork for child & executing command
void	child_exec(t_pipex *p)
{
	char	*cmd_with_path;
	t_lcmd	*todo;
	char	**env_pipe;

	p->pid = improved_fork();
	env_pipe = env_list_to_env_tab();
	todo = get_node_pipes(p->commands, p->idx);
	if (p->pid < 0)
		return (perror("Fork"));
	if (p->pid == 0)
	{
		// printf("list fd read: %d and write %d, p->idx: %d\n", todo->fd_read, todo->fd_write, p->idx);
		sub_dup2(todo->fd_read, todo->fd_write);
		close_pipes(p);
		cmd_with_path = get_right_path(todo->cmd);
		if (!cmd_with_path)
		{
			// msg(ERR_CMD);													//set error msg
			free_two_dimension_array(env_pipe);
			exit(1);
		}
		if (execve(cmd_with_path, todo->option, env_pipe) < 0)
		{
			free_two_dimension_array(env_pipe);
			return (perror(ERR_EXEC "(parent)"));
		}
		free_two_dimension_array(env_pipe);
	}
}
