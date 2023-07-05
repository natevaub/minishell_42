/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:23:28 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/09 16:10:03 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	size_t	index;
	char	*pt1_conv;
	char	*pt2_conv;

	pt1_conv = (char *)pointer1;
	pt2_conv = (char *)pointer2;
	index = 0;
	if (size == 0)
		return (0);
	while ((index < size - 1) && (*pt1_conv == *pt2_conv))
	{
		pt1_conv++;
		pt2_conv++;
		index++;
	}
	if (size == 0)
		return (0);
	return ((unsigned char)*pt1_conv - (unsigned char)*pt2_conv);
}
