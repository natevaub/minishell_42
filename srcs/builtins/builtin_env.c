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

//ENV WITH NO OPTIONS OR ARGUMENTS
/*If no utility is specified, env prints out the names and values
of the variables in the environment, with one name/value pair per line.*/

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
int	print_env(t_minishell *ms)
{
	t_venv	*head;

	head = global.copy_env;
	while (head)
	{
		if (find_c(head->word, '='))
		{
			ft_putstr_fd(head->word, ms->cmd->fd_write);								//adjust fd if redirection
			ft_putchar_fd('\n', ms->cmd->fd_write);
		}
		head = head->next;
	}
	ft_putstr_fd("_=/usr/bin/env\n", ms->cmd->fd_write);								//adjust fd if redirection
	return(EXIT_SUCCESS);
}