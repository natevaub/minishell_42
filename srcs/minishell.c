#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char				*prompt;
	struct sigaction	s;

	init_signals(&s);
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGQUIT, &s, NULL);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = readline(">> ");
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