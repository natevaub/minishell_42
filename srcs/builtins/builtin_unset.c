/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_builtin_others.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/05 17:08:20 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//UNSET WITH NO OPTIONS
/*Using the unset command, you can unset values and attributes of shell
variables.*/
int	cmd_unset(char **var)
{
	t_venv	*list;
	t_venv	*pre_copy;
	t_venv	*post_copy;

	while (*var)
	{
		list = global.copy_env;
		while (list)
		{
			if (ft_strncmp(list->word, *var, ft_strlen(*var)) == 0)
			{
				pre_copy = list->prev;
				post_copy = list->next;
				if (pre_copy)
					pre_copy->next = post_copy;
				if (post_copy)
						post_copy->prev = pre_copy;
				free(list->word);
				free(list);
			}
			list = list->next;
		}
		var++;
	}
	return (EXIT_SUCCESS);
}