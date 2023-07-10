/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/05 14:59:10 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	{
		printf("in first error check var: %s\n", var);
			err = -1;
	}
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

//check if a variable exists in environment
bool	existing_var_in_env(char *var, t_venv *head)
{
	char	*copy_var;
	int		len;

	copy_var = trim_back(var);
	// printf("trimmed var: \n%s\n", copy_var);
	len = ft_strlen(copy_var);
	while (head)
	{
		if (ft_strncmp(head->word, copy_var, len) == 0)
		{
			free(copy_var);
			return (true);
		}
		head = head->next;
	}
	free(copy_var);
	return (false);
}

//add *var to env tableau
int	add_var_to_export(char **var, t_venv **head)
{
	t_venv	*addback;
	t_venv	*pre_copy;
	t_venv	*post_copy;

	while (*var)
	{
		if (check_var_format(*var) == EXIT_FAILURE)
			return (EXIT_FAILURE);								//included error msg here (bash: export: `=1': not a valid identifier)
		if (existing_var_in_env(*var, *head) == true)
			cmd_unset(trim_back(*var), head);
		if (insert_node_in_list(*var, head) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		var++;
	}
		return (EXIT_SUCCESS);
}

//cmd: export (without args), prints env in ascii order without the last arg path
int	print_export(t_venv *env_for_export)
{
	char	**lines;

	//check if last history was "minishell", if yes, add line list_append() with "_="/bin/bash""
	bubble_sort(&env_for_export);
	while (env_for_export)
	{
		lines = ft_split(env_for_export->word, '=');
		if (!lines)
			return (errno);												//included errno here
		ft_printf("declare -x %s=%c", lines[0], '"');
		if (lines[1])
			ft_printf("%s", lines[1]);
		ft_printf("%c\n", '"');
		env_for_export = env_for_export->next;
		free(lines[0]);
		free(lines[1]);
		free(lines);
	}
	return (EXIT_SUCCESS);
}
