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
	t_venv *current = env_list;
	t_venv *next;

	while (current != NULL)
	{
		next = current->next;

		// Free the memory for the variables in the current node
		// Assuming that the 'name' field is a dynamically allocated string
		free(current->word);

		// Free the current node itself
		free(current);

		current = next;
	}
}