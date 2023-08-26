/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_decide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/23 12:26:44 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// extern g_global	global;

/* function assesses if argument is a built in*/
int	builtin_check(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp(cmd, "minishell", ft_strlen(cmd)) == 0)
		return (1);
	else
		return (0);
}

/*if yes, checks if there are given arguments
and redirects to right builtin function for execution*/
void	builtin_run(t_minishell *ms, t_lcmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)) == 0)
		ms->last_exit_status = cmd_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)) == 0)
		ms->last_exit_status = cmd_cd(cmd, ms);
	else if (ft_strncmp(cmd->cmd, "pwd", ft_strlen(cmd->cmd)) == 0)
		ms->last_exit_status = cmd_pwd(cmd);
	else if (ft_strncmp(cmd->cmd, "export", ft_strlen(cmd->cmd)) == 0)
	{
		if (!(cmd->option[1]))
			ms->last_exit_status = print_export(cmd, ms);
		else
			ms->last_exit_status = add_var_to_export((cmd->option) + 1, ms);
	}
	else if (ft_strncmp(cmd->cmd, "unset", ft_strlen(cmd->cmd)) == 0)
	{
		if ((ms->cmd->option) + 1)
			ms->last_exit_status = cmd_unset((cmd->option) + 1, ms);
	}
	else if (ft_strncmp(cmd->cmd, "env", ft_strlen(cmd->cmd)) == 0)
		ms->last_exit_status = print_env(ms, cmd);
	else if (ft_strncmp(cmd->cmd, "exit", ft_strlen(cmd->cmd)) == 0)
		cmd_exit(ft_atoi(*((cmd->option) + 1)), ms);
	else if (ft_strncmp(cmd->cmd, "minishell", ft_strlen(cmd->cmd)) == 0)
		change_shvl_in_env(1, ms);
}
