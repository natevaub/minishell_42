/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:53:54 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/21 15:54:17 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_syntax_quote_check(char *str)
{
	int		i;
	int		open;

	open = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			open = ft_syntax_open_quote_check(str, str[i], &i);
		}
		else
			i++;
	}
	if (open == 1)
		return (1);
	return (0);
}

int	ft_syntax_open_quote_check(char *str, char c, int *i)
{
	(*i)++;
	while (str[*i] != '\0')
	{
		if (str[*i] == c)
		{
			(*i)++;
			return (0);
		}
		(*i)++;
	}
	return (1);
}
