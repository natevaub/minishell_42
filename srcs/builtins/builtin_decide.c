/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_decide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 19:10:09 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// extern g_global	global;

/* function assesses if argument is a built in*/
// int	builtin_check(char *cmd)
// {
// 	if (!cmd)
// 		return (0);
// 	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
// 		return (1);
// 	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
// 		return (1);
// 	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
// 		return (1);
// 	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
// 		return (1);
// 	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
// 		return (1);
// 	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
// 		return (1);
// 	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
// 		return (1);
// 	else if (ft_strncmp(cmd, "minishell", ft_strlen(cmd)) == 0)
// 		return (1);
// 	else
// 		return (0);
// }

// Check for exact matches of built-in commands
int	builtin_check(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!cmd)
		return (0);
	if (cmd[0] != '\0' && (ft_strcmp(cmd, "echo") == 0 || \
		ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || \
		ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 || \
		ft_strcmp(cmd, "env") == 0 || \
		ft_strcmp(cmd, "exit") == 0 || \
		ft_strcmp(cmd, "minishell") == 0))
	{
		return (1);
	}
	return (0);
}

void	builtin_run(t_minishell *ms, t_lcmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		ms->last_exit_status = cmd_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ms->last_exit_status = cmd_cd(cmd, ms);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ms->last_exit_status = cmd_pwd(cmd);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
	{
		if (!(cmd->option[1]))
			ms->last_exit_status = print_export(cmd, ms);
		else
			ms->last_exit_status = add_var_to_export((cmd->option) + 1, ms);
	}
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
	{
		if ((ms->cmd->option) + 1)
			ms->last_exit_status = cmd_unset((cmd->option) + 1, ms);
	}
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ms->last_exit_status = print_env(ms, cmd);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		cmd_exit(cmd, ms);
	else if (ft_strcmp(cmd->cmd, "minishell") == 0 || \
		ft_strcmp(cmd->cmd, "./minishell") == 0)
		change_shvl_in_env(1, ms);
}
