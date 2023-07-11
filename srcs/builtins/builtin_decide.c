/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_decide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/11 10:46:40 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
void	builtin_redirect(t_global *global, char *cmd, char **option)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		global->last_exit_status = cmd_echo(option, global, true, true);	//TBC
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		global->last_exit_status = cmd_cd(global->copy_env, *option);		//ready
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		global->last_exit_status = cmd_pwd();								//ready
	else if (ft_strncmp(cmd, "export", 6) == 0)
	{
		if (!*option)
			global->last_exit_status = print_export(global->copy_env);
		else if (*option)
			global->last_exit_status = add_var_to_export(option, &(global->copy_env));		//ready
	}
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		global->last_exit_status = cmd_unset(option, &(global->copy_env));				//ready
	else if (ft_strncmp(cmd, "env", 3) == 0)
		global->last_exit_status = print_env(global->copy_env);
	else if (ft_strncmp(cmd, "exit", 4) == 0)								//TBC
		cmd_exit(global->last_exit_status);
}
