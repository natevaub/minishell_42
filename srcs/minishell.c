#include "../includes/minishell.h"

t_global		global;

int main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;
	char				**option;
	char				*cmd;

	ft_init_minishell(&shell, envp);
	init_signals();

	// change_shvl_in_env(1);
	// prompt = ft_output_command_line();
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


// t_minishell *ms = malloc(sizeof(t_minishell));

// 	char	*prompt;


// 	prompt = ft_output_command_line();
// 	ft_printf("%s\n", prompt);
// 	ft_tokenize_prompt(ms, prompt);
// 	ft_printlist_tk(ms->token);