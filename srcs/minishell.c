#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_minishell *ms = malloc(sizeof(t_minishell));

	char	*prompt;


	prompt = readline(">> ");
	ft_printf("%s\n", prompt);
	ft_tokenize_prompt(ms, prompt);
	ft_printlist_tk(ms->token);

	return (0);
}