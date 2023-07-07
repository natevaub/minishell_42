/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/29 18:39:07 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	list_size(t_venv *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_venv	*last_node(t_venv *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_venv	*first_node(t_venv *lst)
{
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_venv	*get_node(t_venv *head, int index)
{
	t_venv	*copy;
	int			i;

	i = 0;
	copy = head;
	while (i < index && copy != NULL)
	{
		copy = copy->next;
		i++;
	}
	return (copy);
}
