/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:34:03 by nvaubien          #+#    #+#             */
/*   Updated: 2023/07/08 22:40:27 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_strjoin(char *s1, char *s2, int s2_size)
{
	char	*joined_str;
	size_t	s2_len;
	size_t	total;
	int		i;
	int		ii;

	i = 0;
	ii = 0;
	s2_len = s2_size;
	total = ft_strlen(s1) + s2_len;
	joined_str = (char *)malloc(sizeof(char) * total + 1);
	if (joined_str == NULL)
		return (NULL);
	while (*s1)
		joined_str[i++] = *s1++;
	while (ii < s2_size)
	{
		joined_str[i++] = *s2++;
		ii++;
	}
	joined_str[total] = '\0';
	return (joined_str);
}

char	*ft_gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

void	ft_gnl_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n-- > 0)
	{
		*(ptr++) = '\0';
	}
}

void	*ft_gnl_calloc(size_t count, size_t size)
{
	void	*str;

	str = (void *)malloc(count * size);
	if (!str)
		return (0);
	ft_gnl_bzero(str, count * size);
	return (str);
}
