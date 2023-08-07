#include "../includes/minishell.h"

t_global		global;

/* Nate's Main :-) */
int main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;

	ft_init_minishell(&shell, envp);
	init_signals();

	while (1)
	{
		prompt = ft_output_command_line();
		if (prompt == NULL)
			exit(0);
		if (prompt)
			add_history(prompt);
		ft_parsing(&shell, prompt);

		if (shell.syntax == 0 && total_len_cmd(shell.cmd) < 2)
		{
			// printf("in exec_pipe_no_pipe\n");
			ft_exec_no_pipe(&shell);
		}
		else
		{
			// printf("in exec_pipe\n");
			// exec_pipe(&shell, envp);
			ft_pipeline_execution(&shell, envp);
		}
		ft_free_parsing(&shell);
	}
	free_env_list(global.copy_env);
	return (0);
}
