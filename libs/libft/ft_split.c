/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:58:34 by nvaubien          #+#    #+#             */
/*   Updated: 2022/11/09 16:10:22 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_strings(char const *s, char c)
{
	size_t	idx;
	size_t	count;

	count = 0;
	idx = 0;
	while (s[idx])
	{
		if (s[idx] != c && (s[idx + 1] == c || s[idx + 1] == '\0'))
			count++;
		idx++;
	}
	return (count);
}

static	char	**gen_memory_strings(char const *s, char c)
{
	char	**strings;
	size_t	count;

	count = count_strings(s, c);
	strings = malloc(sizeof(char *) * (count + 1));
	if (strings == NULL)
		return (NULL);
	return (strings);
}

static	size_t	find_next_valid(char const *s, char c, size_t idx)
{
	while (s[idx] == c)
	{
		idx++;
	}
	return (idx);
}

static	size_t	len_str(char const *s, char c, size_t idx)
{
	size_t	count;

	count = 0;
	while (s[idx] != c && s[idx] != '\0')
	{
		count++;
		idx++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	size_t	i;
	size_t	stri;
	size_t	curri;

	stri = 0;
	i = 0;
	strings = gen_memory_strings(s, c);
	if (!strings)
		return (0);
	while (i < ft_strlen(s))
	{
		i = find_next_valid(s, c, i);
		if (!s[i])
			break ;
		curri = len_str(s, c, i);
		strings[stri] = ft_substr(s, i, curri);
		stri++;
		i += curri;
	}
	strings[stri] = 0;
	return (strings);
}
