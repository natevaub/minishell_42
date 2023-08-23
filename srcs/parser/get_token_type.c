/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/23 11:05:24 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtins(char *prompt)
{
	if (ft_strcmp(prompt, D_ECHO) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_CD) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_PWD) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_EXPORT) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_UNSET) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_ENV) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_EXIT) == 0)
		return (1);
	return (0);
}

int	ft_is_red(char *prompt)
{
	if (ft_strcmp(prompt, D_INFILE) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_OUTFILE) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_HEREDOC) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_APPEND) == 0)
		return (1);
	return (0);
}

int	ft_red_type(char *prompt)
{
	if (*prompt == '\0')
	{
		return (E_NORED);
	}
	else if (ft_strcmp(prompt, D_INFILE) == 0)
	{
		return (E_INFILE);
	}
	else if (ft_strcmp(prompt, D_OUTFILE) == 0)
	{
		return (E_OUTFILE);
	}
	else if (ft_strcmp(prompt, D_HEREDOC) == 0)
	{
		return (E_HEREDOC);
	}
	else if (ft_strcmp(prompt, D_APPEND) == 0)
	{
		return (E_APPEND);
	}
	return (E_NORED);
}

int	ft_is_pipe(char *prompt)
{
	if (ft_strcmp(prompt, D_PIPE) == 0)
		return (1);
	return (0);
}

int	ft_is_space(char *prompt)
{
	if (*prompt == ' ' || *prompt == '\t')
		return (1);
	return (0);
}
