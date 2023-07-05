/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:31:21 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/07 15:37:55 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*fct)(void *), void (*del)(void *))
{
	t_list	*element;
	t_list	*lst2;

	lst2 = NULL;
	while (lst)
	{
		element = ft_lstnew(fct(lst->content));
		if (!element)
			ft_lstclear(&lst2, del);
		ft_lstadd_back(&lst2, element);
		lst = lst->next;
	}
	return (lst2);
}
