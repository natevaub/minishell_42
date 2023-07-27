/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_decide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/24 11:59:13 by nvaubien         ###   ########.fr       */
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
	else if (ft_strncmp(cmd, "minishell", 9) == 0)
		return (1);
	else
		return (0);
}

/*if yes, checks if there are given arguments
and redirects to right builtin function for execution*/
void	builtin_redirect(t_minishell *ms)
{
	if (!ms->cmd->cmd)
		return ;																	//add error msg
	if (ft_strncmp(ms->cmd->cmd, "echo", 4) == 0)
		global.last_exit_status = cmd_echo(ms);
	else if (ft_strncmp(ms->cmd->cmd, "cd", 2) == 0)
		global.last_exit_status = cmd_cd(ms);
	else if (ft_strncmp(ms->cmd->cmd, "pwd", 3) == 0)
		global.last_exit_status = cmd_pwd();
	else if (ft_strncmp(ms->cmd->cmd, "export", 6) == 0)
	{
		if (!(ms->cmd->option[1]))
			global.last_exit_status = print_export(ms);
		else
			global.last_exit_status = add_var_to_export((ms->cmd->option) + 1);
	}
	else if (ft_strncmp(ms->cmd->cmd, "unset", 5) == 0)
	{
		if((ms->cmd->option) + 1)
			global.last_exit_status = cmd_unset((ms->cmd->option) + 1);
	}
	else if (ft_strncmp(ms->cmd->cmd, "env", 3) == 0)
		global.last_exit_status = print_env(ms);
	else if (ft_strncmp(ms->cmd->cmd, "exit", 4) == 0)
		cmd_exit(*((ms->cmd->option) + 1));
	else if (ft_strncmp(ms->cmd->cmd, "minishell", 9) == 0)
		change_shvl_in_env(1);
}
