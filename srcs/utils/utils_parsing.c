/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:28:22 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 15:16:07 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *str, char *comp)
{
	int	i;

	i = 0;
	if (!str || !comp)
		return (1);
	while (str[i] == comp[i] && str[i] != '\0' && comp[i] != '\0')
	{
		i++;
	}
	return (str[i] - comp[i]);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	if (!src)
		return (dest);
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	ft_open_failed(t_lcmd *cmd, t_minishell *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	ms->last_exit_status = 1;
	cmd->fd_read = 0;
	exit (1);
}

void	ft_permission_denied(t_lcmd *cmd, t_minishell *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	ms->last_exit_status = 1;
	cmd->fd_write = 1;
	exit (1);
}
