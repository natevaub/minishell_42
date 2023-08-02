#include "../../includes/minishell.h"

void	child_exec_no_pipe(t_minishell *ms, char **env_tab)
{
	char	*cmd_with_path;
	pid_t	pid;

	pid = improved_fork();
	if (pid < 0)
		return (perror("Fork"));
	if (pid == 0)
	{
		sub_dup2(ms->cmd->fd_read, ms->cmd->fd_write);
		cmd_with_path = get_right_path(ms->cmd->cmd);
		if (!cmd_with_path)
		{
			global.last_exit_status = 1;										//check if this is correct
		}
		if (execve(cmd_with_path, ms->cmd->option, env_tab) < 0)
		{
			return (perror("Execve"));
		}
	}
	// else
	// 	waitpid(-1, NULL, 0);
}

void	ft_exec_no_pipe(t_minishell *ms)
{
	char	**env_tab;

	env_tab = env_list_to_env_tab();
	if (ms->cmd->cmd != NULL)
	{
		if ((builtin_check(ms->cmd->cmd)) == 1)
			builtin_redirect(ms->cmd);
		else
		{
			child_exec_no_pipe(ms, env_tab);
			waitpid(-1, NULL, 0);
		}
	}
	free_two_dimension_array(env_tab);
}