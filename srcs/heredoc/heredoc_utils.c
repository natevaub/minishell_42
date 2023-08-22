/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 02:38:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/22 22:48:16 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_heredoc_eof_util(t_tok *tok)
{
	char	*eof;
	t_tok	*start;

	eof = NULL;
	start = tok;
	while (tok->type == E_SPACE)
	{
		tok = tok->next;
	}
	if (tok->type == E_STRING)
	{
		eof = ft_strdup(tok->word);
	}
	printf("EOF = %s\n", eof);
	tok = start;
	return (eof);
}

char	*ft_get_heredoc_eof(t_minishell *shell)
{
	t_tok	*start;
	char	*eof;

	eof = NULL;
	start = shell->token;
	while (ft_strcmp(shell->token->word, D_HEREDOC) != 0)
	{
		shell->token = shell->token->next;
	}
	shell->token = shell->token->next;
	eof = ft_get_heredoc_eof_util(shell->token);
	shell->token = start;
	return (eof);
}

int	ft_heredoc_detected(t_minishell *shell)
{
	t_tok	*start;

	start = shell->token;
	while (shell->token != NULL)
	{
		if (ft_strcmp(shell->token->word, D_HEREDOC) == 0)
		{
			shell->token = start;
			return (1);
		}
		shell->token = shell->token->next;
	}
	shell->token = start;
	return (0);
}

bool	ft_eof_quoted(char *eof)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(eof))
	{
		if (eof[i] == '\'' || eof[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

t_linked_list	*ft_get_heredocs(t_tok *tokens)
{
	t_linked_list	*delims;
	t_tok			*ref;

	ref = tokens;
	delims = NULL;
	while (tokens != NULL)
	{
		if (ft_strncmp(tokens->word, D_HEREDOC, 2) == 0)
		{
			tokens = tokens->next;
			while (tokens != NULL && tokens->type == E_SPACE)
			{
				tokens = tokens->next;
			}
			if (tokens && tokens->type == E_STRING)
			{
				delims = ft_insert_at_tail(delims, ft_strdup(tokens->word));
				tokens = tokens->next;
			}
		}
		else
			tokens = tokens->next;
	}
	tokens = ref;
	return (delims);
}
