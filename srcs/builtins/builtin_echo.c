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
if option is $?, we need to print last exit status*/
int	cmd_echo(char **option)
{
	char	*print;
	bool	backslash;

	option++;
	if (*option && ft_strncmp(*option, "-n", 2) == 0)
	{
		backslash = false;
		option++;
	}
	else
		backslash = true;
	while (*option != 0)
	{
		// if (*option[0] == '$' && (*option + 1))					//expand variable if necessary
		// {
		// 	if	(existing_var_in_env(*option + 1) == true)
		// 		print = get_value(global.copy_env, *option + 1);
		// 	else
		// 		print = ft_strdup(*option);		//or print nothing if ""
		// }
		if (!(print = ft_strdup(*option)))
			return (errno);
		if (*(option + 1) != NULL)
			ft_printf("%s ", print);
		else
			ft_printf("%s", print);
		free(print);
		option++;
	}
	if (backslash == true)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}