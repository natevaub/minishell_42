/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/05 18:04:42 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (ft_strncmp(env->element, var, len) == 0)
			value = env->element;
		env = env->next;
	}
	return (ft_strdup(value + len + 1));
}

/*check if var is in env table, if yes, need to print its value and not the var name,
check quotes ('$USER' should output $USER), inner and outer*/
int	cmd_echo(char **cmd, char *option, t_venv *head, bool single_quotes, bool double_quotes)
{
	char	*print;
	(void)	single_quotes;
	(void)	double_quotes;

	while (*cmd != 0)
	{
		if (*cmd[0] == '$' && (*cmd + 1))
		{
			if	(existing_var_in_env(*cmd + 1, head) == true)
				print = get_value(head, *cmd + 1);	//prints the value found in env
			else
				print = ft_strdup(*cmd);		//or print nothing if ""
		}
		else if (!(print = ft_strdup(*cmd)));
			return (errno);
		if (option && ft_strncmp(option, "-n", 2) == 0)
			ft_printf("print without backslash n: %s", print);					//need to print % at the end like for cat
		else
			ft_printf("print with backslash n: %s\n", print);
		free(print);
		cmd++;
	}
	return (EXIT_SUCCESS);
}