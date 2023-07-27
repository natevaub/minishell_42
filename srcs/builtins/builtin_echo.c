/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/24 12:25:05 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//ECHO WITH OPTION -N
/*The echo utility writes any specified operands, separated by single blank (` ')
characters and followed by a newline (`\n') character, to the standard output.
-n option: Do not print the trailing newline character.*/

//get variable value from env
char	*get_value(t_venv *env, void *var)
{
	char	*value;
	int		len;

	len = ft_strlen((char *)var);
	while (env)
	{
		if (ft_strncmp(env->word, var, len) == 0)
			value = env->word;
		env = env->next;
	}
	return (ft_strdup(value + len + 1));
}

/*check if var is in env table, if yes, need to print its value and not the var name,
check quotes ('$USER' should output $USER), inner and outer
if option is $?, we need to print last exit status
>>>var is already expanded if necessary*/
int	cmd_echo(t_minishell *ms)
{
	bool	backslash;
	int		i;

	i = 1;
	backslash = true;
	if (!((ms->cmd->option)[i]))
	{
		ft_putstr_fd("\n", 1);								//adjust fd if redirection
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp((ms->cmd->option)[i], "-n", 2) == 0)
	{
		backslash = false;
		i++;
	}
	while ((ms->cmd->option)[i] != 0)
	{
		ft_putstr_fd((ms->cmd->option)[i], 1);								//adjust fd if redirection
		if ((ms->cmd->option)[i + 1] != 0)
			ft_putstr_fd(" ", 1);								//adjust fd if redirection
		i++;
	}
	if (backslash == true)
		ft_putstr_fd("\n", 1);								//adjust fd if redirection
	return (EXIT_SUCCESS);
}