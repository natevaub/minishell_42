#include "../includes/minishell.h"

int	ft_exec_builtins(t_minishell *ms)
{
	if (ms->cmd->cmd != NULL)
	{
		if ((builtin_check(ms->cmd->cmd)) == 1)
			builtin_redirect(ms);
	}
	return (global.last_exit_status);
}