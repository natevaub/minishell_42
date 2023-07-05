/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:03:14 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/08 14:34:55 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_empty(t_list *lst)
{
	if (lst == NULL)
		return (1);
	else
		return (0);
}

int	ft_lstsize(t_list *lst)
{
	size_t	size;

	size = 0;
	if (!is_empty(lst))
	{
		while (lst != NULL)
		{
			size++;
			lst = lst->next;
		}
	}
	return (size);
}
