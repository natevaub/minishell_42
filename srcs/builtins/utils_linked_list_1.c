/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/18 13:41:35 by ckarl            ###   ########.fr       */
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

t_venv	*get_node_venv(t_venv *head, int index)
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

//append new node to list
void	list_append(t_venv **lst, char *element)
{
	t_venv	*addback;
	t_venv	*copy;

	addback = (t_venv *)malloc(sizeof(t_venv));
	if (!addback)
		return ;
	addback->next = NULL;
	addback->word = ft_strdup(element);
	if (!addback->word)							//add error message
		return ;
	if (*lst == NULL)
	{
		*lst = addback;
		addback->prev = NULL;
		return ;
	}
	copy = last_node(*lst);
	copy->next = addback;
	addback->prev = copy;
}
