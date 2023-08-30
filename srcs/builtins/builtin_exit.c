/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 17:51:28 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*if "minishell" is called again (nbr = 1), we need to increase SHLVL variable,
when exit is called (nbr = -1), we need to decrease it*/
void	change_shvl_in_env(int nbr, t_minishell *ms)
{
	int		shlvl_int;
	char	*shlvl_char;
	char	*shlvl_changed;
	t_venv	*head;

	shlvl_char = get_value(ms->copy_env, "SHLVL");
	shlvl_int = ft_atoi(shlvl_char);
	if (nbr == 1)
		shlvl_changed = ft_itoa(shlvl_int + 1);
	else
		shlvl_changed = ft_itoa(shlvl_int - 1);
	shlvl_char = ft_strjoin("SHLVL=", shlvl_changed);
	free(shlvl_changed);
	head = ms->copy_env;
	while (head)
	{
		if (ft_strncmp(head->word, "SHLVL", head->len) == 0)
		{
			free(head->word);
			head->word = shlvl_char;
		}
		head = head->next;
	}
}

//1 for numberic, 2 for too many arguments
void	ft_exit_error_msg(char *opt, t_minishell *ms, int option)
{
	if (option == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ms->last_exit_status = 255;
	}
	else if (option == 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ms->last_exit_status = 1;
	}
}

//check if arg is not a valid nr
int	ft_exit_arg_check(char *str, t_minishell *ms, t_lcmd *cmd)
{
	int				i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0' || i > 20)
	{
		ft_exit_error_msg(str, ms, 1);
		return (0);
	}
	if (cmd->option[2])
	{
		ft_exit_error_msg(str, ms, 2);
		return (1);
	}
	run_exit_atoi(str, ms);
	return (0);
}

//EXIT WITH NO OPTIONS
/*The exit() function causes normal process termination and the
least significant byte of status (i.e., status & 0xFF) is
returned to the parent (see wait(2)).*/
void	cmd_exit(t_lcmd *cmd, t_minishell *ms)
{
	char	*tmp;
	int		flag;

	flag = 0;
	if (*(cmd->option + 1))
	{
		flag = ft_exit_arg_check(*(cmd->option + 1), ms, cmd);
	}
	if (flag != 1)
	{
		tmp = get_value(ms->copy_env, "SHLVL");
		if (ft_strncmp("1", tmp, 1) == 0)
		{
			ft_putstr_fd("exit\n", 1);
			exit(ms->last_exit_status);
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			change_shvl_in_env(-1, ms);
		}
	}
}
