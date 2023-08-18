/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:13:31 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/18 17:11:56 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
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
