/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/23 11:04:56 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len_red(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] == c)
		len++;
	return (len);
}

int	ft_len_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && (str[len] == ' ' || str[len] == '\t'))
		len++;
	return (len);
}

int	ft_len_word(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		if (str[len] == '<' || str[len] == '>' || \
			str[len] == '|' || str[len] == ' ')
			break ;
		len++;
	}
	return (len);
}

int	ft_len_quote(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
		if (str[len] == c)
		{
			len++;
			break ;
		}
	}
	return (len);
}
