/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/08 09:35:14 by nvaubien         ###   ########.fr       */
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

char	*ft_join_path(char const *s1, char const *s2)
{
	char			*copy;
	int				i;
	int				j;
	unsigned int	len1;
	unsigned int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	j = 0;
	copy = (char *)malloc(sizeof(*copy) * (len1 + len2 + 1));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i++] = '/';
	while (s2[j])
		copy[i++] = s2[j++];
	copy[i] = '\0';
	return (copy);
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
		if (access(temp_path, F_OK | X_OK) == 0)
		{
			return (temp_path);
		}
		free(temp_path);
		all_paths++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
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
