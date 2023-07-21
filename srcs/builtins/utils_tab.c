/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/20 17:36:27 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	total_len_tab(char **tab)
{
	int	len;

	len = 0;
	while (*tab)
	{
		len += ft_strlen(*tab);
		tab++;
	}
	return (len);
}

char	*ft_strndup(char *s, char n)
{
	int		size;
	int		index;
	char	*dup;

	index = 0;
	size = ft_strlen(s);
	if (n == 0)
		return (NULL);
	dup = malloc(sizeof(char) * size);
	if (!dup)
		return (0);
	while (index < size && s[index] != n)
	{
		dup[index] = s[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}
