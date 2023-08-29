/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/29 22:56:16 by ckarl            ###   ########.fr       */
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

//regular atoi using long long int
long long int	ft_longatoi_for_shell(char *str, t_minishell *ms)
{
	int						i;
	unsigned long long int	result;
	int						neg;
	long long int			end;
	(void) ms;

	result = 0;
	neg = 1;
	i = 0;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || result > 9223372036854775807)
		return (-1);
	else if (neg == -1)
		end = (result * neg) % 256;
	else if (result > 255)
		end = result % 256;
	else
		end = result;
	return (end);
}

//check if arg is not a valid nr
int	ft_exit_arg_error(char *str, t_minishell *ms, t_lcmd *cmd)
{
	int				i;
	long long int	ex_status;

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
	ex_status = ft_longatoi_for_shell(str, ms);
	if (ex_status == -1 || ex_status > 255)
	{
		ft_exit_error_msg(str, ms, 1);
		return (0);
	}
	ms->last_exit_status = ex_status;
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
		flag = ft_exit_arg_error(*(cmd->option + 1), ms, cmd);
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
