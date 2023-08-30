/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:19:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 19:59:41 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_fill_word(char *word, int *start, int *i)
{
	char	*new;
	int		j;
	int		len;

	j = 0;
	while (word[*i] != '\0' && word[*i] != '$')
	{
		(*i)++;
	}
	len = *i - *start;
	new = ft_calloc(sizeof(char), (len + 1));
	if (!new)
		return (NULL);
	while (j < len)
	{
		new[j] = word[*start];
		(*start)++;
		j++;
	}
	return (new);
}

char	*ft_fill_word_expand(char *word, int *start, int *i)
{
	char	*new;
	int		j;
	int		len;

	j = 0;
	while (word[*i] != '\0' && word[*i] != '$')
	{
		if (word[*i] == ' ' || word[*i] == '"' || word[*i] == '\'')
			break ;
		(*i)++;
	}
	len = *i - *start;
	new = ft_calloc(sizeof(char), (len + 1));
	if (!new)
		return (NULL);
	while (j < len)
	{
		new[j] = word[*start];
		(*start)++;
		j++;
	}
	return (new);
}

char	*ft_get_venv_value(char *word, int *start, int *i, t_minishell *ms)
{
	char	*new;
	char	*venv;

	new = NULL;
	if (word[*start] == '$')
	{
		if (word[*start + 1] == '?')
		{
			new = ft_expand_last_exit_status(ms);
			(*start) += 2;
			(*i) += 2;
		}
		else
		{
			(*start)++;
			(*i)++;
			venv = ft_fill_word_expand(word, i, start);
			new = ft_strdup(get_value(ms->copy_env, venv));
			if (new == NULL)
				new = ft_strdup("");
			free(venv);
		}
	}
	return (new);
}

int	ft_token_has_dollar(char *word)
{
	int		i;
	char	c;

	i = 0;
	c = '$';
	while (word[i] != '\0')
	{
		if (word[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_join_array(char **temp)
{
	int		i;
	int		size;
	char	*joined;

	i = 0;
	size = 0;
	while (temp[i] != NULL)
	{
		size += ft_strlen(temp[i]);
		i++;
	}
	i = 0;
	joined = ft_calloc(sizeof(char), size + 1);
	while (temp[i] != NULL)
	{
		joined = ft_strcat(joined, temp[i]);
		i++;
	}
	return (joined);
}
