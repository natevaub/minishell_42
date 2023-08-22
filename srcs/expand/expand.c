/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:20:58 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/22 21:36:10 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expand_token(t_minishell *shell)
{
	t_tok	*start;

	start = shell->token;
	while (shell->token != NULL)
	{
		if (ft_token_has_dollar(shell->token->word) == 1)
		{
			if (shell->token->quote == E_SINGLE)
			{
				shell->token = shell->token->next;
			}
			else
			{
				ft_expand_venv(shell, shell->token->word);
				shell->token = shell->token->next;
			}
		}
		else
		{
			shell->token = shell->token->next;
		}
	}
	shell->token = start;
}

char	*ft_expand_last_exit_status(t_minishell *ms)
{
	int	status;

	status = ms->last_exit_status;
	ms->last_exit_status = 0;
	return (ft_itoa(status));
}

void	ft_expand_venv(t_minishell *shell, char	*word)
{
	int		i;
	int		j;
	int		start;
	char	*temp[256];
	char	*new_tok;

	i = 0;
	j = 0;
	start = 0;
	while (word[i] != '\0')
	{
		if (word[i] != '$')
		{
			temp[j] = ft_fill_word(word, &i, &start);
		}
		else if (word[i] == '$')
		{
			temp[j] = ft_dollar_alone(word, &i, &start);
			if (temp[j] == NULL)
				temp[j] = ft_get_venv_value(word, &i, &start, shell);
		}
		j++;
	}
	temp[j] = NULL;
	new_tok = ft_join_array(temp);
	if (shell->token->word)
		free(shell->token->word);
	shell->token->word = new_tok;
	// free(new_tok);
}

char	*ft_dollar_alone(char *word, int *start, int *i)
{
	char	*new;

	new = NULL;
	if (word[*start + 1] == ' ' || word[*start + 1] == '\0')
	{
		new = ft_calloc(sizeof(char), 2);
		new[0] = word[*start];
		(*start)++;
		(*i)++;
	}
	return (new);
}
