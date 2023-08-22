/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/22 16:29:21 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//UNSET WITH NO OPTIONS
/*Using the unset command, you can unset values and attributes of shell
variables.*/
int	cmd_unset(char **option, t_minishell *ms)
{
	t_venv	*list;
	t_venv	*pre_copy;
	t_venv	*post_copy;

	while (*option)
	{
		list = ms->copy_env;
		while (list)
		{
			if (ft_strncmp(list->word, *option, ft_strlen(*option)) == 0)
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
		option++;
	}
	return (EXIT_SUCCESS);
}
