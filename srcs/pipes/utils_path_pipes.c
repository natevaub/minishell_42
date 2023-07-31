/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/13 16:30:35 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//get entire text line following "PATH=" from envp
char	*get_path_line(void)
{
	char	*envp_path;
	t_venv	*head;

	head = global.copy_env;
	while (head)
	{
		if (ft_strncmp(head->word, "PATH", 4) == 0)
			envp_path = head->word;
		head = head->next;
	}
	return (envp_path + 5);
}

/*find the right path for a specific command (without parameters)
in order to pass it to envp in child/parent using access check function
(existing & executable)*/
char	*get_right_path(char *cmd)
{
	char	**all_paths;
	char	*temp_path;

	all_paths = ft_split(get_path_line(), ':');
	while (*all_paths)
	{
		temp_path = ft_join_path(*all_paths, cmd);
		if (access(temp_path, F_OK & X_OK) == 0)
			return (temp_path);
		free(temp_path);
		all_paths++;
	}
	return (NULL);
}
