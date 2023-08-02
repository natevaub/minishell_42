/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/02 14:35:07 by ckarl            ###   ########.fr       */
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
	t_lcmd	*curr;

	global.last_exit_status = 0;
	env_tab = env_list_to_env_tab();
	ms->p = malloc(sizeof(t_pipex));
	if (!ms->p)
		return (1);																	//set errno
	init_pipex_struct(ms);
	while (ms->p->idx < ms->p->count_cmds)
	{
		curr = get_node_lcmd(ms->cmd, ms->p->idx);
		if (builtin_check(curr->cmd) == 1)
		{
			printf("in builtin-redirect pipe\n");
			builtin_redirect(curr);
		}
		else
		{
			printf("in child exec\n");
			child_exec(ms, env_tab);
			// waitpid(-1, NULL, 0);
		}
		// waitpid(-1, NULL, 0);
		free(curr);
		ms->p->idx++;
	}
	close_pipes(ms->p);
	waitpid(-1, NULL, 0);
	printf("finished loop (after waitpid) in pipe_exec\n");
	free_two_dimension_array(env_tab);
	return (global.last_exit_status);																//exits the program, why?
}

//function creating fork for child & executing command
void	child_exec(t_minishell *ms, char **env_tab)
{
	char	*cmd_with_path;
	t_lcmd	*to_do;
	pid_t	pid;

	pid = improved_fork();
	to_do = get_node_lcmd(ms->cmd, ms->p->idx);
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
			global.last_exit_status = 1;
		}
		if (execve(cmd_with_path, to_do->option, env_tab) < 0)
		{
			return (perror("Execve"));
		}
	}
}
