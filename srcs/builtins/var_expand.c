/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/20 14:55:25 by ckarl            ###   ########.fr       */
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
				expanded = ft_strdup(head->word[len_word + 1]);
			else
				expanded = ft_strdup("");
			return (expanded);
		}
		head = head->next;
	}
	return (ft_strdup(""));
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
	return (expanded_tab);
}

char	*expand_join(char *front, char *trimmed, char *value)
{
	char	*joined;
	int		i;
	int		len;
	char	**exp_tab;

	i = 0;
	exp_tab = expanded_tab(trimmed);
	len = ft_strlen(front) + total_len_tab(exp_tab) + ft_strlen(value);
	joined = (char *)malloc(len + 1);
	if (!joined)
		return (NULL);															//include error here
	while (*front)
		joined[i++] = *front++;
	while (*exp_tab)
	{
		while (**exp_tab)
			joined[i++] = **exp_tab++;
		exp_tab++;
	}
	while (*value)
		joined[i++] = *value++;
	joined[i] = '\0';
	free_two_dimension_array(exp_tab);
	return (joined);
}

//expand variable if necessary
char	*get_expand_var(char *var)
{
	char	*trimmed;
	char	*value;
	char	*front;
	char	*expanded_str;
	int		len;

	trimmed = trim_back(var);
	len = ft_strlen(trimmed);
	if (find_c(trimmed, '$') == 0 || len == 1)
	{
		free(trimmed);
		return (var);
	}
	// if (var + len)
	value = ft_strdup(var + len);
	front = ft_strndup(var, '$');
	expanded_str = expand_join(front, value, trimmed);
	if (!expanded_str)
		return (NULL);													//include error here
	free(trimmed);
	free(front);
	free(value);
	return (expanded_str);
}
