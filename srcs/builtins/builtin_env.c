/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/08 13:29:37 by nvaubien         ###   ########.fr       */
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
int	print_env(t_minishell *ms, t_lcmd *cmd)
{
	t_venv	*head;

	head = ms->copy_env;
	while (head)
	{
		if (find_c(head->word, '='))
		{
			// Redirect output to the input of the next command in the pipeline
			ft_putstr_fd(head->word, cmd->fd_write);								//adjust fd if redirection
			ft_putchar_fd('\n', cmd->fd_write);
		}
		head = head->next;
	}
	ft_putstr_fd("_=/usr/bin/env\n", cmd->fd_write);								//adjust fd if redirection
	return(EXIT_SUCCESS);
}
