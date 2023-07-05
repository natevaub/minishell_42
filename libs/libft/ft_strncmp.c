/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:13:31 by nvaubien          #+#    #+#             */
/*   Updated: 2022/10/28 14:31:20 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n - 1) && (*s1 == *s2) && (*s1))
	{
		i++;
		s1++;
		s2++;
	}
	if (n == 0)
		return (0);
	return ((unsigned char )*s1 - (unsigned char)*s2);
}
