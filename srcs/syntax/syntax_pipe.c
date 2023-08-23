/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/23 11:09:52 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_syntax_pipe_check(t_tok *syntax)
{
	if (syntax->type == E_PIPE)
	{
		if (ft_pipe_error(syntax) == 1)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ft_pipe_error(t_tok *syntax)
{
	t_tok	*cpy;

	cpy = syntax;
	while (cpy->prev != NULL && cpy->prev->type == E_SPACE)
		cpy = cpy->prev;
	if (cpy->prev != NULL)
	{
		if (cpy->prev->type != E_STRING)
			return (1);
	}
	if (cpy->prev == NULL)
		return (1);
	cpy = syntax;
	while (cpy->next != NULL && cpy->next->type == E_SPACE)
		cpy = cpy->next;
	if (cpy->next != NULL)
	{
		if (cpy->next->type != E_STRING && cpy->next->type != E_REDIRECTION)
			return (1);
	}
	if (cpy->next == NULL)
		return (1);
	return (0);
}
