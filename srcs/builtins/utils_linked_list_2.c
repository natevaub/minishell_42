/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/07 17:40:51 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

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

//insert a new node after the 10th node in the list
int	insert_node_in_list(char *var, t_venv **head)
{
	t_venv	*addback;
	t_venv	*pre_copy;
	t_venv	*post_copy;

	addback = (t_venv *)malloc(sizeof(t_venv));
	if (!addback)													//included errno here
		return (EXIT_FAILURE);
	addback->word = ft_strdup(var);
	if (!addback->word)											//included errno here
		return (EXIT_FAILURE);
	pre_copy = get_node(*head, 10);
	post_copy = pre_copy->next;
	pre_copy->next = addback;
	post_copy->prev = addback;
	addback->prev = pre_copy;
	addback->next = post_copy;
	return (EXIT_SUCCESS);
}