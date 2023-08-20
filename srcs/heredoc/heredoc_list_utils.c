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
	new_node->value = ft_strdup(content);
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