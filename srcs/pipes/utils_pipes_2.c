/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:06:29 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 19:36:19 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
char	*ft_get_path_line(t_minishell *ms)
{
	char	*envp_path;
	t_venv	*head;

	envp_path = NULL;
	head = ms->copy_env;
	while (head)
	{
		if (ft_strncmp(head->word, "PATH", head->len) == 0)
		{
			envp_path = head->word;
			return (envp_path + 5);
		}
		head = head->next;
	}
	return (NULL);
}

char	*ft_join_path(char const *s1, char const *s2)
{
	char			*copy;
	int				i;
	int				j;
	unsigned int	len1;
	unsigned int	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	j = 0;
	copy = (char *)malloc(sizeof(*copy) * (len1 + len2 + 2));
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

void	ft_cmd_not_found_error(char *cmd, char **all_paths)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_two_dimension_array(all_paths);
}

//get the right path for a cmd
char	*ft_get_right_path(char *cmd, t_minishell *ms)
{
	char	**all_paths;
	char	*temp_path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	all_paths = ft_split(ft_get_path_line(ms), ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		temp_path = ft_join_path(all_paths[i], cmd);
		if (!temp_path)
			return (NULL);
		if (access(temp_path, F_OK | X_OK) == 0)
		{
			free_two_dimension_array(all_paths);
			return (temp_path);
		}
		free(temp_path);
		i++;
	}
	ft_cmd_not_found_error(cmd, all_paths);
	return (NULL);
}
