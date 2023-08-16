#include "../../includes/minishell.h"

extern g_global	global;

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
		signal(SIGINT, SIG_DFL);											//does not give exactly the right result, check how to silence SIG_INT in child and reinitialise in parent
		sub_dup2(ms->cmd->fd_read, ms->cmd->fd_write);
		cmd_with_path = ft_get_right_path(ms->cmd->cmd, ms);
		if (!cmd_with_path)
		{
			ms->last_exit_status = 1;										//check if this is correct & set error msg
		}
		if (execve(cmd_with_path, ms->cmd->option, env_tab) < 0)
		{
			free(cmd_with_path);
			exit(127);
		}
	}
	waitpid(pid, &exit_status, 0);
	if (WIFSIGNALED(exit_status) == true)
		{
			if (WTERMSIG(exit_status) == SIGQUIT)
				write(1, "Quit: 3\n", 8);
			else if (WTERMSIG(exit_status) == SIGINT)
				write(1, "\n", 1);
			ms->last_exit_status = 128 + exit_status;
		}
	if (WIFEXITED(exit_status))
		ms->last_exit_status = WEXITSTATUS(exit_status);
}

void	ft_exec_no_pipe(t_minishell *ms, char **envp)
{
	if (ms->cmd->cmd != NULL)
	{
		if ((builtin_check(ms->cmd->cmd)) == 1)
		{
			builtin_run(ms, ms->cmd);
		}
		else
		{
			child_exec_no_pipe(ms, envp);
		}
	}
}