/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/06/22 12:28:28 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//join two strings and add '/' at the end
char	*ft_join_path(char const *s1, char const *s2)
{
	char			*copy;
	int				i;
	int				j;
	unsigned int	len1;
	unsigned int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	j = 0;
	copy = (char *)malloc(sizeof(*copy) * (len1 + len2 + 1));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i++] = '/';
	while (s2[j])
		copy[i++] = s2[j++];
	copy[i] = '\0';
	return (copy);
}

char	**env_list_to_env_tab(void)
{
	char	**env;
	int		len;
	t_venv	*head;
	int		i;

	i = 0;
	head = global.copy_env;
	len = list_size(head);
	env = (char **)malloc (sizeof(char *) * (len + 1));
	while (head)
	{
		env[i] = ft_strdup(head->word);
		if (!env[i])
			return (NULL);															//set error msg
		i++;
		head = head->next;
	}
	env[i] = 0;

	return (env);
}