/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/18 11:42:28 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

/*if "minishell" is called again (nbr = 1), we need to increase SHLVL variable,
when exit is called (nbr = -1), we need to decrease it*/
void	change_shvl_in_env(int nbr)
{
	int		shlvl_int;
	char	*shlvl_char;
	char	*shlvl_changed;
	t_venv	*head;

	shlvl_char = get_value(global.copy_env, "SHLVL");
	shlvl_int = ft_atoi(shlvl_char);
	free(shlvl_char);
	if (nbr == 1)
		shlvl_changed = ft_itoa(shlvl_int + 1);
	else if (nbr == -1)
		shlvl_changed = ft_itoa(shlvl_int - 1);
	shlvl_char = ft_strjoin("SHLVL=", shlvl_changed);
	free(shlvl_changed);
	head = global.copy_env;
	while (head)
	{
		if (ft_strncmp(head->word, "SHLVL", 5) == 0)
		{
			free(head->word);
			head->word = shlvl_char;
		}
		head = head->next;
	}
}


//EXIT WITH NO OPTIONS
/*The exit() function causes normal process termination and the
least significant byte of status (i.e., status & 0xFF) is
returned to the parent (see wait(2)).*/
void	cmd_exit(char *status)
{
	if (ft_strncmp("1", get_value(global.copy_env, "SHLVL"), 1) == 0)
	{
		if (status)
			global.last_exit_status = ft_atoi(status);
		exit(global.last_exit_status);
	}
	else
		change_shvl_in_env(-1);
}

/*
	$? codes:
	127 = error code (bash: asdf: command not found)
	1 = error code (ls: o: No such file or directory), combination of valid command and invalid option
	0 = everything correct
*/