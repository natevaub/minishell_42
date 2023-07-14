#include "../includes/minishell.h"

t_global		global;

/* Christina's Main :D */
/*
int main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;
	char				**option;
	char				*cmd;

	ft_init_minishell(&shell, envp);
	init_signals();

	while (1)
	{
		prompt = readline(">> ");
		if (prompt == NULL)//Exit on Ctrl-D, very slow, takes about 3 - 5 seconds
			exit(0);
		if (prompt)
			add_history(prompt);
		option = ft_split(prompt, ' ');
		cmd = option[0];
		if (option + 1)
			builtin_redirect(cmd, (option + 1));
		else
			builtin_redirect(cmd, NULL);
	}
	return (0);
}
*/

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
		if (prompt == NULL) //Exit on Ctrl-D, very slow, takes about 3 - 5 seconds
			exit(0);
		if (prompt)
			add_history(prompt);
		ft_tokenize_prompt(&shell, prompt);
		ft_printlist_tk(shell.token);
		ft_parse_token(&shell);
		ft_print_cmds(shell.cmd);
		
	}
	return (0);
}