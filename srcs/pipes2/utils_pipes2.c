/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/07 17:04:58 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//max nbr of commands
int	ft_count_cmds(t_lcmd *cmd)
{
	t_lcmd	*cpy;
	int		i;

	cpy = cmd;
	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	cmd = cpy;
	return (i);
}

//get the PATH line from env
char	*ft_get_path_line(void)
{
	char	*envp_path = NULL;
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

//get the right path for a cmd
char	*ft_get_right_path(char *cmd)
{
	char	**all_paths;
	char	*temp_path;

	all_paths = ft_split(ft_get_path_line(), ':');
	while (*all_paths)
	{
		temp_path = ft_join_path(*all_paths, cmd);
		if (access(temp_path, F_OK & X_OK) == 0)
		{
			return (temp_path);
		}
		free(temp_path);
		all_paths++;
	}
	return (NULL);
}

void	ft_init_pipes_struct(t_minishell *shell, t_pipex *pipe)
{
	pipe->count_cmds = ft_count_cmds(shell->cmd);
	pipe->idx = 0;
}

int		ft_pipe_dep_mod(t_pipex *p)
{
	if (p->idx % 2 == 0)
	{
		pipe(p->pipe_fd[0]);
	}
	else
	{
		pipe(p->pipe_fd[1]);
	}
	return (0);
}
