/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/18 15:00:26 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//save value ("=xyz") in a char *value
//check how many $ there are, check each if existing in var

//check for $ (even if more than one)
char	*check_expand_in_env(char *trimmed)
{
	char	*expanded;
	char	*check;

	while (*trimmed)
	{
		if (*trimmed == '$')
		{
			while (*trimmed != '$' && *trimmed)
			{
				check = (char *)malloc(50);
				if (!check)
					return (NULL);									//include error here
				*check++ = *trimmed++;
			}
			*check = '\0';
		}
		trimmed++;
	}

}

char	**get_expand_tab(char *trimmed)
{
	char	**tab;

	tab = ft_split(trimmed, '$');
	if (!tab)
		return (NULL);
	//get expand_tab with the expanded values
	return (tab);
}

//expand variable if necessary
char	*get_expand_var(char *var)
{
	char	*exp_var;
	char	*trimmed;
	char	*value;
	t_venv	*head;
	int		len;

	head = global.copy_env;
	trimmed = trim_back(var);
	len = ft_strlen(trimmed);
	if (find_c(trimmed, '$') == 0 || len == 1)
	{
		free(trimmed);
		return (var);
	}
	value = ft_strdup(var + len);
	//need to save front in exp_var if trimmed[0] != '$', then get_expand_tab

}