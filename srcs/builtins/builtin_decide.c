/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_decide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/22 16:11:39 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// extern g_global	global;

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
	else if (ft_strncmp(cmd, "minishell", 9) == 0)
		return (1);
	else
		return (0);
}

/*if yes, checks if there are given arguments
and redirects to right builtin function for execution*/
void	builtin_run(t_minishell *ms, t_lcmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		ms->last_exit_status = cmd_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		ms->last_exit_status = cmd_cd(cmd, ms);
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		ms->last_exit_status = cmd_pwd(cmd);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		if (!(cmd->option[1]))
			ms->last_exit_status = print_export(cmd, ms);
		else
			ms->last_exit_status = add_var_to_export((cmd->option) + 1, ms);
	}
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
	{
		if ((ms->cmd->option) + 1)
			ms->last_exit_status = cmd_unset((cmd->option) + 1, ms);
	}
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ms->last_exit_status = print_env(ms, cmd);
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		cmd_exit(ft_atoi(*((cmd->option) + 1)), ms);
	else if (ft_strncmp(cmd->cmd, "minishell", 9) == 0)
		change_shvl_in_env(1, ms);
}
