#include "../includes/minishell.h"

// char	*ft_get_command_line(void)
// {
// 	char	*cmd_line;

// 	cmd_line = malloc(sizeof(char) * (MAXPATHLEN + 3));
// 	if (getcwd(cmd_line, MAXPATHLEN + 3) == NULL)
// 		perror("getcwd() error");
// 	else
// 	{
// 		ft_strcat(cmd_line, "$ ");
// 	}
// 	return (cmd_line);
// }

char	*ft_get_command_line(void)
{
	char	*cmd_line;

	cmd_line = malloc(sizeof(char) * (MAXPATHLEN + 3));
	if (getcwd(cmd_line, MAXPATHLEN + 3) == NULL)
		perror("getcwd() error");
	else
	{
		char* home_path = getenv("HOME");
		if (home_path != NULL && strncmp(cmd_line, home_path, strlen(home_path)) == 0)
		{
			// Replace home directory with ~
			ft_memmove(cmd_line, "~", 1);
			ft_memmove(cmd_line + 1, cmd_line + strlen(home_path), strlen(cmd_line) - strlen(home_path) + 1);
		}
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