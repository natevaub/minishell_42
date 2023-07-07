#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*prompt;

	prompt = readline(">> ");
	ft_printf("%s\n", prompt);
	char *res = ft_get_word(&prompt);
	printf("%s\n", res);
	return (0);
}