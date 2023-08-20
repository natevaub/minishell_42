/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_joined_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 02:10:35 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/19 02:11:22 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_joinable(t_tok *token)
{
	if (token->next != NULL)
	{
		if (token->type == E_REDIRECTION || token->type == E_PIPE)
			return (1);
		else if (token->type == E_STRING && token->next->type == E_PIPE)
			return (1);
		else if (token->type == E_STRING && token->next->type == E_REDIRECTION)
			return (1);
	}
	return (0);
}

int	ft_join_tk(t_tok *tk)
{
	char	*new_word;
	int		i;
	int		j;

	while (tk != NULL)
	{
		if (ft_is_joinable(tk) == 1)
			tk = tk->next;
		else if (tk->next != NULL && *tk->word != ' ' && *tk->next->word != ' ')
		{
			i = 0;
			j = 0;
			new_word = ft_calloc(sizeof(char), \
				ft_strlen(tk->word) + ft_strlen(tk->next->word) + 1);
			if (!new_word)
				return (1);
			ft_strcat_join_tk(new_word, tk->word, &i, &j);
			i = 0;
			ft_strcat_join_tk(new_word, tk->next->word, &i, &j);
			ft_get_joined_tk(tk, new_word);
		}
		else
			tk = tk->next;
	}
	return (0);
}

void	ft_strcat_join_tk(char *s1, char *s2, int *i, int *j)
{
	while (s2[*i] != '\0')
	{
		s1[*j] = s2[*i];
		(*i)++;
		(*j)++;
	}
}

void	ft_get_joined_tk(t_tok *tok, char *n_tk)
{
	t_tok	*curr;

	free(tok->word);
	tok->word = n_tk;
	curr = tok->next;
	tok->next = curr->next;
	free(curr->word);
	free(curr);
}
