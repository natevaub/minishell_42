#include "../includes/minishell.h"

g_global		global;

int main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;

	ft_init_minishell(&shell, envp);
	while (1)
	{
		// ft_init_signals(signal_prompt_handler);
		ft_init_signals(signal_exec_handler);
		prompt = ft_output_command_line();

		if (prompt == NULL)
			exit(0);
		if (prompt)
			add_history(prompt);
		ft_parsing(&shell, prompt);
		if (shell.syntax == 0)
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
	}
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &shell.termios_default)) == -1)
		exit(EXIT_FAILURE);
	free_env_list(shell.copy_env);
	return (0);
}
