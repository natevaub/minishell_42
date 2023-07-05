/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:05:33 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/08 14:37:57 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	index;
	int	last_occ;

	index = 0;
	last_occ = -1;
	while (s[index] != '\0')
	{
		if (s[index] == (char) c)
		{
			last_occ = index;
		}
		index++;
	}
	if (last_occ >= 0)
	{
		return ((char *)(s + last_occ));
	}
	if (s[index] == (char) c)
	{
		return ((char *)(s + index));
	}
	return (NULL);
}
