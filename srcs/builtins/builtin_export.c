/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/02 12:26:22 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//EXPORT WITH NO OPTIONS (BUT WITH POTENTIAL ARGUMENTS)
/*Normally, when you run a command at the bash prompt, a dedicated process is
created with its own environment, exclusively for running your command. Any
variables and functions you defined before running the command are not shared
with new processes — unless you explicitly mark them with export.
Example: myvar="This variable is defined." > export myvar > bash > echo $myvar >
"This variable is defined."*/

//check if var is in allowed format (no #, $ or @ in name, starts with letter or _)
int	check_var_format(char *var)
{
	int		i;
	int		err;

	i = 0;
	if (((var[0] > 'Z' && var[0] < 'a') || var[0] < 'A' \
		|| var[0] > 'z') && var[0] != '_')
		err = -1;
	while (var[i] != '=' && var[i] && err != -1)
	{
		if (var[i] == '#' || var[i] == '@' || var[i] == '$')
			err = -1;
		i++;
	}
	if (err == -1)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//trim the end of str to get only the var name (without the value if there is any)
char	*trim_back(char *var)
{
	char	*untrimmed;
	char	*trimmed;
	int		x;

	untrimmed = (char *)var;
	if (find_c(untrimmed, '=') == 0)
	{
		trimmed = ft_strdup(untrimmed);
		return (trimmed);
	}
	trimmed = (char *)malloc(sizeof(char) * (ft_strlen(untrimmed) + 1));
	if (!trimmed)
		return (NULL);																//include error msg here
	x = -1;
	while (untrimmed[++x] && untrimmed[x] != '=')
		trimmed[x] = untrimmed[x];
	trimmed[x] = '\0';
	return (trimmed);
}

//check if a variable exists in environment & change it to *var
int	change_existing_var_in_env(char *var)
{
	char	*copy_var;
	int		len;
	t_venv	*head;

	head = global.copy_env;
	copy_var = trim_back(var);
	len = ft_strlen(copy_var);
	while (head)
	{
		if (ft_strncmp(head->word, copy_var, len) == 0 && \
		(head->word[len] == '=' || head->word[len] == '\0'))
		{
			free(head->word);
			head->word = ft_strdup(var);
			free(copy_var);
			return (1);
		}
		head = head->next;
	}
	free(copy_var);
	return (0);
}

//add *var to env tableau
int	add_var_to_export(char **option)
{
	while (*option)
	{
		if (check_var_format(*option) == EXIT_FAILURE)
			return (EXIT_FAILURE);								//included error msg here (bash: export: `=1': not a valid identifier)
		if (change_existing_var_in_env(*option) == 0)
		{
			if (insert_node_in_list(*option, &global.copy_env) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		option++;
	}
		return (EXIT_SUCCESS);
}

//cmd: export (without args), prints env in ascii order without the last arg path
//check if last history was "minishell", if yes, add line list_append() with "_="/bin/bash""
int	print_export(t_lcmd *cmd)
{
	char	**lines;
	t_venv	*env_for_export;

	env_for_export = global.copy_env;
	bubble_sort(&env_for_export);
	while (env_for_export)
	{
		lines = ft_split(env_for_export->word, '=');
		if (!lines)
			return (errno);
		ft_putstr_fd("declare -x ", cmd->fd_write);											//adjust fd if redirection
		ft_putstr_fd(lines[0], cmd->fd_write);
		ft_putstr_fd("=", cmd->fd_write);
		ft_putchar_fd('"', cmd->fd_write);
		if (lines[1])
			ft_putstr_fd(lines[1], cmd->fd_write);
		ft_putchar_fd('"', cmd->fd_write);
		ft_putchar_fd('\n', cmd->fd_write);
		env_for_export = env_for_export->next;
		free_two_dimension_array(lines);
	}
	return (EXIT_SUCCESS);
}
