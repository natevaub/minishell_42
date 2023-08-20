/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 02:38:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/20 02:38:31 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_list_to_char_expands(t_linked_list *head)
{
	int				total_size;
	t_linked_list	*curr;
	char			*str;

	str = NULL;
	curr = head;
	total_size = 0;
	// DBG("Here in list to char expands");
	while (curr != NULL)
	{
		ft_replace_node_content(curr);
		total_size += ft_strlen(curr->value);
		curr = curr->next;
	}
	curr = head;
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

void	*ft_replace_node_content(t_linked_list *node)
{
	int		i;
	int		j;
	char	*ret;
	char	*val;
	char	*val_env;

	i = 0;
	j = 0;
	ret = ft_strdup("");
	while (node->value[i] != '\0')
	{
		// DBG("In while");
		if (node->value[i] == '$' && node->value[i + 1] != ' ')
		{
			i++;
			while (node->value[i] != ' ' && node->value[i] != '$' && node->value[i] != '\0')
			{
				j++;
				i++;
			}
			val = ft_substr(node->value, i - j, j);
			val_env = getenv(val);
			// DBG(val_env);
			if (val_env != NULL)
			{
				ft_strcat(ret, val_env);
			}
			free(val);
			j = 0;
		}
		else
		{
			ret = ft_strjoin(ret, ft_substr(node->value, i, 1));
			i++;
		}
	}
	free(node->value);
	node->value = ret;
	// DBG(node->value);
}
