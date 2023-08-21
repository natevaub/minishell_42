/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:54:55 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/21 15:56:19 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_syntax_red_check(t_tok *tok)
{
	if ((tok->red == E_OUTFILE || tok->red == E_INFILE) && tok->next != NULL)
	{
		if (ft_red_error(tok) == 1)
			return (1);
	}
	else if ((tok->red == E_OUTFILE || tok->red == E_INFILE)
		&& tok->next == NULL)
		return (1);
	else if ((tok->red == E_HEREDOC || tok->red == E_APPEND)
		&& tok->next != NULL)
	{
		if (ft_red_error(tok) == 1)
			return (2);
	}
	else if ((tok->red == E_HEREDOC || tok->red == E_APPEND)
		&& tok->next == NULL)
		return (2);
	return (0);
}

int	ft_red_error(t_tok *tk)
{
	t_tok	*cpy;

	cpy = tk;
	while (cpy->next->type == E_SPACE)
	{
		cpy = cpy->next;
		if (cpy->next == NULL)
			return (1);
	}
	if (cpy->next->type != E_STRING)
		return (1);
	return (0);
}
