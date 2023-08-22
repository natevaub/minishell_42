/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 06:55:20 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/22 21:52:38 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	size_t	start_trim(char const *s1, char const *set)
{
	size_t	idx_set;
	size_t	idx_str;

	idx_set = 0;
	idx_str = 0;
	while (set[idx_set])
	{
		while (set[idx_set] == s1[idx_str])
		{
			idx_str++;
			idx_set = 0;
		}
		idx_set++;
	}
	return (idx_str);
}

static	size_t	end_trim(char const *s1, char const *set)
{
	size_t	idx_set;
	size_t	idx_end;

	idx_set = 0;
	idx_end = ft_strlen(s1) - 1;
	while (set[idx_set])
	{
		while (set[idx_set] == s1[idx_end])
		{
			idx_end--;
			idx_set = 0;
		}
		idx_set++;
	}
	return (idx_end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	int		size_malloc;
	size_t	start;

	start = start_trim(s1, set);
	size_malloc = end_trim(s1, set) - start_trim(s1, set) + 1;
	strtrim = ft_substr(s1, start, size_malloc);
	if (strtrim == NULL)
		return (NULL);
	free((char *)s1);
	return (strtrim);
}
