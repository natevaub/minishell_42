#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_global			vgl;
	t_minishell			shell;
	char				*prompt;
	struct sigaction	s;

	ft_init_minishell(&shell, &vgl, envp);
	init_signals(&s);
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGQUIT, &s, NULL);
	signal(SIGQUIT, SIG_IGN);
	// prompt = ft_output_command_line();
	while (1)
	{
		prompt = readline(">> ");
		if (prompt == NULL)//Exit on Ctrl-D
		{
			// printf("\n");
			exit(0);
		}
		if (prompt)
			add_history(prompt);
	}
	return (0);
}


// t_minishell *ms = malloc(sizeof(t_minishell));

// 	char	*prompt;


// 	prompt = ft_output_command_line();
// 	ft_printf("%s\n", prompt);
// 	ft_tokenize_prompt(ms, prompt);
// 	ft_printlist_tk(ms->token);