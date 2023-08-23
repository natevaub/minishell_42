/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/23 11:08:31 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_word_space(char **str)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc(sizeof(char), ft_len_space(*str) + 1);
	if (!word)
		return (NULL);
	while (**str && (**str == ' ' || **str == '\t'))
	{
		word[i] = (**str);
		i++;
		(*str)++;
	}
	return (word);
}

char	*ft_get_word_red(char **str, char c)
{
	char	*word;
	int		i;

	word = ft_calloc(sizeof(char), ft_len_red(*str, c) + 1);
	i = 0;
	if (!word)
		return (NULL);
	while (**str == c)
	{
		word[i] = **str;
		i++;
		(*str)++;
	}
	return (word);
}

char	*ft_get_word_quote(char **prompt, char c)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc(sizeof(char), ft_len_quote(*prompt, c) + 1);
	if (!word)
		return (NULL);
	word[i] = (**prompt);
	i++;
	(*prompt)++;
	while (**prompt != '\0')
	{
		word[i] = (**prompt);
		if (**prompt == c)
			break ;
		i++;
		(*prompt)++;
	}
	if (**prompt == c)
		(*prompt)++;
	return (word);
}

char	*ft_get_word(char **str)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc(sizeof(char), ft_len_word(*str) + 1);
	if (!word)
		return (NULL);
	while (**str != '\0')
	{
		if (**str == '\'' || **str == '\"')
			break ;
		else if (**str == '|' || **str == '<' || **str == '>' || **str == ' ')
			break ;
		word[i] = **str;
		(*str)++;
		i++;
	}
	return (word);
}
