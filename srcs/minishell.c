#include "../includes/minishell.h"

t_global		global;

/* Nate's Main :-) */
int main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;

	ft_init_minishell(&shell, envp);
	// init_signals();

	while (1)
	{
		ft_init_signals(signal_prompt_handler);
		prompt = ft_output_command_line();
		ft_init_signals(signal_exec_handler);
		if (prompt == NULL)
			exit(0);
		if (prompt)
			add_history(prompt);
		ft_parsing(&shell, prompt);
		if (shell.syntax == 0)
		{
			DBG("10");
			if (ft_count_cmds(shell.cmd) < 2)
			{
				ft_exec_no_pipe(&shell, envp);
			}
			else
			{
				ft_pipeline_execution(&shell, envp);
			}
		}
		ft_free_parsing(&shell);
	}
	free_env_list(global.copy_env);
	return (0);
}
