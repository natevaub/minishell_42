/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/20 18:21:30 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//get the expanded value of a var from global.copy_env
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
				expanded = ft_strdup(head->word + len_word + 1);
			else
				expanded = ft_strdup("");
			return (expanded);
		}
		head = head->next;
	}
	return (ft_strdup(""));
}

//get the expanded values of all vars in a **tab
char	**expanded_tab(char *trimmed)
{
	char	**tab;
	char	**expanded_tab;
	int		i;

	tab = ft_split(trimmed, '$');
	if (!tab)
		return (NULL);
	expanded_tab = (char **)malloc(sizeof(char *) * (tab_size(tab) + 1));
	if (!expanded_tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		expanded_tab[i] = expanded_value(tab[i]);
		i++;
	}
	expanded_tab[i] = 0;
	free_two_dimension_array(tab);
	return (expanded_tab);
}

//join the **expanded_tab to a *char
char	*expanded_join(char *front, char **exp_tab, char *value)
{
	char	*joined;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	joined = (char *)malloc(ft_strlen(front) + total_len_tab(exp_tab) \
			+ ft_strlen(value) + 1);
	if (!joined)
		return (NULL);																				//include error here
	while (*front)
		joined[i++] = *front++;
	while (exp_tab[j])
	{
		k = 0;
		while (exp_tab[j][k])
			joined[i++] = exp_tab[j][k++];
		j++;
	}
	while (*value)
		joined[i++] = *value++;
	joined[i] = '\0';
	free_two_dimension_array(exp_tab);
	return (joined);
}

//expand variable if necessary, keep front and back the same
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
	value = ft_strdup(var + len);
	front = ft_strndup(var, '$');
	expanded_str = expanded_join(front, expanded_tab(trimmed), value);
	if (!expanded_str)
		return (NULL);													//include error here
	free(trimmed);
	free(front);
	free(value);
	return (expanded_str);
}
