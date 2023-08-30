/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 17:36:17 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//regular atoi using long long int
long long int	ft_longatoi_for_shell(char *str)
{
	int						i;
	unsigned long long int	result;
	int						neg;
	long long int			end;

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
	end = (result * neg) % 256;
	return (end);
}

void	run_exit_atoi(char *str, t_minishell *ms)
{
	long long int	ex_status;

	ex_status = ft_longatoi_for_shell(str);
	if (ex_status == -1 || ex_status > 255)
	{
		ft_exit_error_msg(str, ms, 1);
		return ;
	}
	ms->last_exit_status = ex_status;
}
