/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:28:13 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/21 16:28:18 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_env_list(t_venv *env_list)
{
	t_venv *current;
	t_venv *next;

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
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &ms->termios_default)) == -1)
		exit(EXIT_FAILURE);
	free_env_list(ms->copy_env);
	free(ms->p);
	exit(EXIT_SUCCESS);
}