/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/18 15:00:26 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//save value ("=xyz") in a char *value
//check how many $ there are, check each if existing in var

//check for $ (even if more than one)
char	*expanded_value(char *word)
{
	char	*expanded;
	int		len_word;
	t_venv	*head;

	head = global.copy_env;
	len_word = ft_strlen(word);
	while (head)
	{
		if (ft_strncmp(head->word, word, len_word) == 0 && \
		(head->word[len_word] == '=' || head->word[len_word] == '\0'))
		{
			if (head->word[len_word + 1])
			{
				expanded = ft_strdup(head->word[len_word + 1]);
				return (expanded);
			}
		}
		head = head->next;
	}
	return (ft_strdup(""));
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}


char	**expanded_tab(char *trimmed)
{
	char	**tab;
	char	**expanded_tab;

	tab = ft_split(trimmed, '$');
	if (!tab)
		return (NULL);
	expanded_tab = (char **)malloc(sizeof(char *) * (tab_size(tab) + 1));
	if (!expanded_tab)
		return (NULL);
	while (*tab)
	{
		*expanded_tab = expanded_value(*tab);
		expanded_tab++;
		tab++;
	}
	*expanded_tab = '\0';
	free_two_dimension_array(tab);
	//get expand_tab with the expanded values
	return (expanded_tab);
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

//expand variable if necessary
char	*get_expand_var(char *var)
{
	char	*trimmed;
	char	*value;
	char	*front;
	t_venv	*head;
	int		len;
	int		i;

	i = 0;
	head = global.copy_env;
	trimmed = trim_back(var);
	len = ft_strlen(trimmed);
	if (find_c(trimmed, '$') == 0 || len == 1)
	{
		free(trimmed);
		return (var);
	}
	if (var + len)
		value = ft_strdup(var + len);
	front = ft_strndup(var, '$');
	//for strjoin, need to check if front == NULL

	//saved front, then get_expand_tab >> join
	free(trimmed);
}