/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/23 11:03:04 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_venv *env_list)
{
	t_venv	*current;
	t_venv	*next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->word)
			free(current->word);
		free(current);
		current = next;
	}
	env_list = NULL;
}

void	ft_finish_minishell(t_minishell *ms)
{
	// if ((tcsetattr(STDIN_FILENO, TCSANOW, &ms->termios_default)) == -1)
	// 	exit(EXIT_FAILURE);
	ft_unset_termios(ms);
	free_env_list(ms->copy_env);
	free(ms->p);
	exit(EXIT_SUCCESS);
}
