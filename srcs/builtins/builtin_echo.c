/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/29 22:35:10 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//get variable value from env
char	*get_value(t_venv *env, void *var)
{
	char	*value;

	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->word, var, env->len) == 0)
		{
			value = env->word;
			if (value + env->len + 1 == NULL)
				return (NULL);
			return (value + env->len + 1);
		}
		env = env->next;
	}
	return (NULL);
}

int	cmd_echo(t_lcmd *cmd)
{
	int		i;

	i = 1;
	if (!((cmd->option)[i]))
	{
		ft_putstr_fd("\n", cmd->fd_write);
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp((cmd->option)[i], "-n", 2) == 0 \
		&& ft_strlen(cmd->option[i]) == 2)
		i++;
	while ((cmd->option)[i] != 0)
	{
		ft_putstr_fd(cmd->option[i], cmd->fd_write);
		if ((cmd->option)[i + 1] != 0)
			ft_putstr_fd(" ", cmd->fd_write);
		i++;
	}
	if (ft_strncmp((cmd->option)[1], "-n", 2) != 0)
		ft_putstr_fd("\n", cmd->fd_write);
	return (EXIT_SUCCESS);
}
