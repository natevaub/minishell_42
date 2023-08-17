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
		cmd_with_path = ft_get_right_path(ms->cmd->cmd, ms);
		if (!cmd_with_path)
			exit(127);												//not sure if I need to set the status or exit directly
		if (execve(cmd_with_path, ms->cmd->option, env_tab) < 0)
		{
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
	if (WIFSIGNALED(exit_status) == true)
	{
		if (WEXITSTATUS(exit_status) == SIGINT)
			ms->last_exit_status = global.status;
	}
	if (WIFEXITED(exit_status) == true)
		ms->last_exit_status = WEXITSTATUS(exit_status);
	else
		ms->last_exit_status = global.status;
}

void	ft_exec_no_pipe(t_minishell *ms, char **envp)
{
	global.status = 0;
	if (ms->cmd->cmd != NULL)
	{
		if ((builtin_check(ms->cmd->cmd)) == 1)
			builtin_run(ms, ms->cmd);
		else
			child_exec_no_pipe(ms, envp);
	}
}