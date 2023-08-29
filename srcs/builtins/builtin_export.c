/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/29 23:21:39 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//check if var is in allowed format (no #, $ or @ in name)
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

//trim back of var
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
		return (NULL);
	x = -1;
	while (untrimmed[++x] && untrimmed[x] != '=')
		trimmed[x] = untrimmed[x];
	trimmed[x] = '\0';
	return (trimmed);
}

//check if a variable exists in environment & change it to *var
int	change_existing_var_in_env(char *var, t_minishell *ms)
{
	char	*copy_var;
	t_venv	*head;

	head = ms->copy_env;
	copy_var = trim_back(var);
	if (copy_var == NULL || ft_strcmp(copy_var, "SHLVL") == 0)
	{
		return (EXIT_FAILURE);
	}
	while (head)
	{
		if (ft_strncmp(head->word, copy_var, head->len) == 0 \
			&& copy_var[head->len] == '\0')
		{
			free(head->word);
			head->word = ft_strdup(var);
			free(copy_var);
			return (1);
		}
		head = head->next;
	}
	free(copy_var);
	return (EXIT_SUCCESS);
}

//add *var to env tableau
int	add_var_to_export(char **option, t_minishell *ms)
{
	int	i;

	i = 0;
	while (option[i])
	{
		if (check_var_format(option[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (change_existing_var_in_env(option[i], ms) == 0)
		{
			if (insert_node_in_list(option[i], ms->copy_env) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//cmd: export (without args), prints env in ascii order
int	print_export(t_lcmd *cmd, t_minishell *ms)
{
	char	**lines;
	t_venv	*env_for_export;

	if (!ms->copy_env)
		return (1);
	env_for_export = ms->copy_env;
	bubble_sort(&env_for_export);
	while (env_for_export)
	{
		lines = ft_split(env_for_export->word, '=');
		if (!lines)
			return (EXIT_FAILURE);
		ft_putstr_fd("declare -x ", cmd->fd_write);
		if (lines[0] != NULL)
			ft_putstr_fd(lines[0], cmd->fd_write);
		ft_putchar_fd('=', cmd->fd_write);
		ft_putchar_fd('"', cmd->fd_write);
		if (lines[1] != NULL)
			ft_putstr_fd(lines[1], cmd->fd_write);
		ft_putchar_fd('"', cmd->fd_write);
		ft_putchar_fd('\n', cmd->fd_write);
		env_for_export = env_for_export->next;
		free_two_dimension_array(lines);
	}
	return (EXIT_SUCCESS);
}
