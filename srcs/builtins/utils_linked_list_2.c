/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_list_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/30 12:59:57 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

//create a new list out of parameter **tab, check **tab for errors
t_venv	*new_env_list(char **tab)
{
	int			a;
	t_venv	*new_list;

	a = 0;
	new_list = NULL;
	while (tab[a + 1])
	{
		list_append(&new_list, tab[a]);
		a++;
	}
	return (new_list);
}

//bubble sort helper, swaps content of two nodes
void	content_swap(t_venv *one, t_venv *two)
{
	t_venv	*temp;

	temp = (t_venv *)malloc(sizeof(t_venv));
	if (!temp)
		return ;
	temp->word = one->word;
	one->word = two->word;
	two->word = temp->word;
	free(temp);
}

//sorts a linked list in ascending order
void	bubble_sort(t_venv **head)
{
	t_venv	*a;
	t_venv	*b;
	int		i;
	int		x;

	i = 0;
	while (i < list_size(*head))
	{
		a = get_node(*head, i);
		x = i + 1;
		while (x < list_size(*head))
		{
			b = get_node(*head, x);
			if (a->word[0] > b->word[0])
				content_swap(a, b);
			x++;
		}
		i++;
	}
}