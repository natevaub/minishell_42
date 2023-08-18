#include "../includes/minishell.h"

char	*ft_list_to_char_expands(t_linked_list *head)
{
	int				total_size;
	t_linked_list	*curr;
	char			*str;

	str = NULL;
	curr = head;
	total_size = 0;
	DBG("Here in list to char expands");
	while (curr != NULL)
	{
		ft_replace_node_content(curr);
	}
	str = (char *)malloc(sizeof(char) * (total_size + 1));
	if (str == NULL)
		ft_memory_allocation_failed();
	curr = head;
	str[0] = '\0';
	while (curr != NULL)
	{
		ft_strcat(str, curr->value);
		ft_strcat(str, "\n");
		curr = curr->next;
	}
	// Free Linked List
	return (str);
}

char	*ft_replace_node_content(t_linked_list *node)
{
	int		i;
	char	*new;
	char	*value;

	i = 0;
	while (node->value[i] != '\0')
	{
		printf("Node->Value[%d] = %c\n", i, node->value[i]);
		i++;
	}
	exit(1);
	return (NULL);
}
