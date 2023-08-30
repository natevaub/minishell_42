/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:54:02 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 13:19:58 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_linked_list	*ft_insert_at_tail(t_linked_list *head, char *content)
{
	t_linked_list	*new_node;
	t_linked_list	*cur;

	new_node = (t_linked_list *)malloc(sizeof(t_linked_list));
	if (new_node == NULL)
	{
		return (head);
	}
	new_node->value = content;
	new_node->next = NULL;
	if (head == NULL)
	{
		return (new_node);
	}
	cur = head;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = new_node;
	return (head);
}

void	free_linked_list(t_linked_list *head)
{
	t_linked_list	*next;

	while (head != NULL)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
}
