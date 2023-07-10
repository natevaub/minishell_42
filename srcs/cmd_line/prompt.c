#include "../includes/minishell.h"

static char	*ft_get_command_line(void)
{
	char	*cmd_line;

	cmd_line = malloc(sizeof(char) * (MAXPATHLEN + 3));
	if (getcwd(cmd_line, MAXPATHLEN + 3) == NULL)
		perror("getcwd() error");
	else
	{
		ft_strcat(cmd_line, "$ ");
	}
	return (cmd_line);
}

char	*ft_output_command_line(void)
{
	char	*prompt_input;
	char	*prompt_output;

	prompt_input = ft_get_command_line();
	prompt_output = readline(prompt_input);
	free(prompt_input);
	return (prompt_output);
}