#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*prompt;

	prompt = readline(">> ");
	ft_printf("%s\n", prompt);
	char *s = "nathan"; char *b = "nathan";
	printf("%d\n", ft_strcmp(s, b));
	free(prompt);
	return (0);
}