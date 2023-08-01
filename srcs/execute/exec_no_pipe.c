#include "../includes/minishell.h"

void	ft_exec_no_pipe(t_minishell *ms)
{
	char	**env_tab;
	char	*cmd_w_path;

	env_tab = env_list_to_env_tab();
	if (!env_tab)
		return(perror("Env tab: "));															//set error msg
	if (ms->cmd->fd_write != 0)
		improved_dup2(ms->cmd->fd_write, STDOUT_FILENO);
	if (ms->cmd->fd_read != 1)
		improved_dup2(ms->cmd->fd_read, STDIN_FILENO);
	if (ms->cmd->cmd != NULL)
	{
		if ((builtin_check(ms->cmd->cmd)) == 1)
			builtin_redirect(ms);
		else
		{
			cmd_w_path = get_right_path(ms->cmd->cmd);
			if (execve(cmd_w_path, ms->cmd->option, env_tab) < 0)
			{
				free(cmd_w_path);
				return (perror("Execve: "));															//set error msg
			}
			// printf("after execve\n");
			free(cmd_w_path);
		}
	}

	// free_two_dimension_array(env_tab);
	// return (global.last_exit_status);
}