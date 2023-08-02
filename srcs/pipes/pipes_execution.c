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
	char	**env_tab;

	env_tab = env_list_to_env_tab();
	ms->p = malloc(sizeof(t_pipex));
	if (!ms->p)
		return (-1);																	//set errno
	init_pipex_struct(ms);
	while (ms->p->idx < ms->p->count_cmds)
	{
		if (builtin_check((get_node_pipes(ms->cmd, ms->p->idx))->cmd) == 1)
		{
			printf("in builtin-redirect pipe\n");
			builtin_redirect(ms);
		}
		else
		{
			printf("in child exec\n");
			child_exec(ms, env_tab);
		}
		ms->p->idx++;
	}
	waitpid(-1, NULL, 0);
	close_pipes(ms->p);
	free_two_dimension_array(env_tab);
	// final_free_and_close(ms);
	// close(ms->infile_fd);
	// close(ms->outfile_fd);
	// exit(0);													//necessary here??
	return (0);
}

//function creating fork for child & executing command
void	child_exec(t_minishell *ms, char **env_tab)
{
	char	*cmd_with_path;
	t_lcmd	*to_do;
	pid_t	pid;

	pid = improved_fork();
	to_do = get_node_pipes(ms->cmd, ms->p->idx);
	if (pid < 0)
		return (perror("Fork"));
	if (pid == 0)
	{
		printf("before execve in child exec\n");
		sub_dup2(to_do->fd_read, to_do->fd_write);
		close_pipes(ms->p);
		cmd_with_path = get_right_path(to_do->cmd);
		if (!cmd_with_path)
		{
			// msg(ERR_CMD);													//set error msg & check if this is correct
			exit(1);
		}
		if (execve(cmd_with_path, to_do->option, env_tab) < 0)
		{
			return (perror("Execve"));
		}
	}
}
