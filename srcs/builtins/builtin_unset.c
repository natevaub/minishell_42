/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 10:44:41 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//UNSET WITH NO OPTIONS
/*Using the unset command, you can unset values and attributes of shell
variables.*/

void	remove_var_from_env(t_venv *list, t_minishell *ms)
{
	t_venv	*pre_copy;
	t_venv	*post_copy;

	if (ft_strncmp(list->word, "SHLVL", list->len) == 0)
		return ;
	pre_copy = list->prev;
	post_copy = list->next;
	if (!pre_copy)
	{
		ms->copy_env = list->next;
		list->next->prev = NULL;
	}
	else
	{
		pre_copy->next = post_copy;
		if (post_copy)
			post_copy->prev = pre_copy;
	}
	free(list->word);
	free(list);
}

int	cmd_unset(char **option, t_minishell *ms)
{
	t_venv	*list;
	t_venv	*temp;
	int		i;

	i = 0;
	while (option[i])
	{
		list = ms->copy_env;
		while (list)
		{
			if (list != NULL && ft_strncmp(list->word, option[i], \
				list->len) == 0 && option[i][list->len] == '\0')
			{
				temp = list;
				list = list->next;
				remove_var_from_env(temp, ms);
			}
			else
				list = list->next;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
