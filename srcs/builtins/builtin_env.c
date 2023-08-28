/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/22 18:22:11 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//find character c in string s, similar to ft_strchr
int	find_c(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

//print environment when command env is called
int	print_env(t_minishell *ms, t_lcmd *cmd)
{
	t_venv	*head;

	head = ms->copy_env;
	if (cmd->option[1])
	{
		ft_path_failed(cmd->cmd);
		return (127);
	}
	while (head)
	{
		if (find_c(head->word, '='))
		{
			ft_putstr_fd(head->word, cmd->fd_write);
			ft_putchar_fd('\n', cmd->fd_write);
		}
		head = head->next;
	}
	ft_putstr_fd("_=/usr/bin/env\n", cmd->fd_write);
	return (EXIT_SUCCESS);
}
