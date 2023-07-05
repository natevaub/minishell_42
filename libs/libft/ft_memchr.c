/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:59 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/08 14:44:19 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*casted_s;

	casted_s = (unsigned char *)s;
	while (n--)
	{
		if (*casted_s == (unsigned char)c)
		{
			return (casted_s);
		}
		casted_s++;
	}
	return (NULL);
}
