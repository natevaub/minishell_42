/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 02:38:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/29 22:45:50 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_list_to_char_expands(t_linked_list *head)
{
	int				total_size;
	t_linked_list	*curr;
	char			*str;

	curr = head;
	total_size = 0;
	while (curr != NULL)
	{
		ft_replace_node_content(curr);
		total_size += ft_strlen(curr->value) + 1;
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
	return (str);
}

int	ft_str_advance(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '$' \
			&& str[i] != '\0' && str[i] != '\'' \
			&& str[i] != '\"')
	{
		i++;
	}
	return (i);
}

void	ft_replace_node_content(t_linked_list *node)
{
	int		i;
	char	*ret;
	char	*val;

	i = -1;
	ret = ft_strdup("");
	while (node->value[++i] != '\0')
	{
		if (node->value[i] == '$' && node->value[i + 1] != ' ')
		{
			i++;
			val = ft_substr(node->value, i, ft_str_advance(&node->value[i]));
			ft_strcat(ret, getenv(val));
			i += ft_str_advance(&node->value[i]);
		}
		else
		{
			val = ft_substr(node->value, i, 1);
			ret = ft_strcat(ret, val);
		}
		free(val);
	}
	free(node->value);
	node->value = ret;
}
