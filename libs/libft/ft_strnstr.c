/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:34:30 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/07 15:49:47 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	idx;
	size_t	l_idx;

	idx = 0;
	l_idx = 0;
	if (!*little)
		return ((char *)big);
	while (idx < len && big[idx])
	{
		l_idx = 0;
		if (big[idx] == little[l_idx])
		{
			while (big[idx + l_idx] == little[l_idx] && idx + l_idx < len
				&& big[idx + l_idx] && little[l_idx++])
			{
				if (!little[l_idx])
					return (((char *)big) + idx);
			}
		}
		idx++;
	}
	return (NULL);
}
