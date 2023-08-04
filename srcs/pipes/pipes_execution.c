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
	// char	**env_tab;
	t_lcmd	*curr;
	pid_t	pid;
	int		exit_status;

	// global.last_exit_status = 0;
	// env_tab = env_list_to_env_tab();
	ms->p = malloc(sizeof(t_pipex));
	if (!ms->p)
		return (1);																	//set errno
	init_pipex_struct(ms);
	while (ms->p->idx < ms->p->count_cmds)
	{
		curr = get_node_lcmd(ms->cmd, ms->p->idx);
		pid = improved_fork();
		if (pid < 0)
			return (error("Fork"));
		if (pid == 0)
		{
			run_cmd(curr, ms->p, envp);
		}
		free(curr);
		ms->p->idx++;;
	}
	close_pipes(ms->p);
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	// if (WIFEXITED(exit_status))
	// 	global.last_exit_status = WEXITSTATUS(exit_status);

	// waitpid(-1, NULL, 0);
	// free_two_dimension_array(env_tab);
	return (global.last_exit_status);																//exits the program, why?
}

void	run_cmd(t_lcmd *cmd, t_pipex *p, char **envp)
{
	if (builtin_check(cmd->cmd) != 1)
	{
		printf("in child exec\n");
		child_exec(cmd, envp, p);
	}
	builtin_redirect(cmd);
}

//function creating fork for child & executing command
void	child_exec(t_lcmd *cmd, char **envp, t_pipex *p)
{
	char	*cmd_with_path;
	// t_lcmd	*to_do;
	// pid_t	pid;

	// pid = improved_fork();
	// to_do = get_node_lcmd(ms->cmd, ms->p->idx);
	// if (pid < 0)
	// 	return (perror("Fork"));
	// if (pid == 0)
	// {
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
		// printf("after execve\n");

	// }
}
