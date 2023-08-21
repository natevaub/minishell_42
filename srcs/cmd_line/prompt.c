/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:21:58 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/21 16:25:50 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_command_line(void)
{
	char	*cmd_line;
	char	*home_path;

	cmd_line = malloc(sizeof(char) * (MAXPATHLEN + 3));
	if (getcwd(cmd_line, MAXPATHLEN + 3) == NULL)
		perror("getcwd() error");
	else
	{
		home_path = getenv("HOME");
		if (home_path != NULL
			&& ft_strncmp(cmd_line, home_path, ft_strlen(home_path)) == 0)
		{
			ft_memmove(cmd_line, "~", 1);
			ft_memmove(cmd_line + 1, cmd_line + ft_strlen(home_path),
				ft_strlen(cmd_line) - ft_strlen(home_path) + 1);
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
