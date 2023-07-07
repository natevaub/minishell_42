/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_decide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/07 17:31:03 by ckarl            ###   ########.fr       */
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
void	builtin_redirect(t_global *global, char *cmd, char *var)
{
	// if (ft_strncmp(cmd, "echo", 4) == 0)
	// 	global->last_exit_status = cmd_echo(cmd, var, global);						//can also be multiple **var
	if (!cmd)
	{
		printf("in !cmd\n");
		return ;
	}
	if (ft_strncmp(cmd, "cd", 2) == 0)
		global->last_exit_status = cmd_cd(var);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		global->last_exit_status = cmd_pwd();
	else if (ft_strncmp(cmd, "export", 6) == 0)
	{
		if (!var)
			global->last_exit_status = print_export(global->copy_env);
		else if (var)
			global->last_exit_status = add_var_export(var, &(global->copy_env));		//can also be multiple **var
	}
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		global->last_exit_status = cmd_unset(var, &(global->copy_env));				//can also be multiple **var
	else if (ft_strncmp(cmd, "env", 3) == 0)
		global->last_exit_status = print_env(global->copy_env);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		cmd_exit(global->last_exit_status);
}