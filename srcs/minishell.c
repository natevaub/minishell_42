#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;
	(void)				ac;
	(void)				av;

	ft_init_minishell(&shell, envp);
	while (1)
	{
		ft_init_signals(signal_exec_handler);
		prompt = ft_output_command_line();
		ft_init_signals(signal_child_handler);
		if (prompt == NULL)
			exit(0);
		if (prompt)
			add_history(prompt);
		ft_parsing(&shell, prompt);
			if (shell.syntax == 0 && shell.last_exit_status != 1)
			{
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
			if (prompt)
				free(prompt);
	}
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &shell.termios_default)) == -1)
		exit(EXIT_FAILURE);
	free_env_list(shell.copy_env);
	free(shell.p);
	return (0);
}
