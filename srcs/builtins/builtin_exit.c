/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_builtin_others.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/05 17:08:20 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

/*if "minishell" is called again (nbr = 1), we need to increase SHLVL variable,
when exit is called (nbr = 0), we need to decrease it*/
void	change_shvl_in_env(int nbr)
{
	int		shlvl_value;
	char	*value;

	value = get_value(global.copy_env, "SHLVL");
	shlvl_value = ft_atoi(value);
	printf("%d\n", shlvl_value);
	// if (nbr == 1)


}


//EXIT WITH NO OPTIONS
/*The exit() function causes normal process termination and the
least significant byte of status (i.e., status & 0xFF) is
returned to the parent (see wait(2)).*/
void	cmd_exit(char *status)
{
	//check SHVL variable, if not 1, then only decrease it and don't exit

	if (status)
		exit(status);
	else
		exit(global.last_exit_status);
}

/*
	$? codes:
	127 = error code (bash: asdf: command not found)
	1 = error code (ls: o: No such file or directory), combination of valid command and invalid option
	0 = everything correct
*/