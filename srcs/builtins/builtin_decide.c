/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_decide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/13 16:33:11 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

/* function assesses if argument is a built in*/
int	builtin_check(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else
	return (0);
}

/*if yes, checks if there are given arguments
and redirects to right builtin function for execution*/
void	builtin_redirect(char *cmd, char **option)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		global.last_exit_status = cmd_echo(option, true, true);	//TBC
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		global.last_exit_status = cmd_cd(*option);		//ready
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		global.last_exit_status = cmd_pwd();								//ready
	else if (ft_strncmp(cmd, "export", 6) == 0)
	{
		if (!*option)
			global.last_exit_status = print_export();
		else if (*option)
			global.last_exit_status = add_var_to_export(option);		//ready
	}
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		global.last_exit_status = cmd_unset(option);				//ready
	else if (ft_strncmp(cmd, "env", 3) == 0)
		global.last_exit_status = print_env();
	else if (ft_strncmp(cmd, "exit", 4) == 0)								//TBC
		cmd_exit(*option);
}
