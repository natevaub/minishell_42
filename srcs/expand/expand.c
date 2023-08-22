/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:38:07 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/22 15:57:06 by nvaubien         ###   ########.fr       */
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

void	ft_skip_dollar_alone(char *word)
{
	if (ft_strlen(word) == 1 && *word == '$')
		return ;
}

char	*ft_expand_last_exit_status(t_minishell *ms)
{
	int	status;

	status = ms->last_exit_status;
	// printf("Last exit status = %d\n", ms->last_exit_status);
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
		// if (word[i] == '$' && (word[i + 1] == ' ' || word[i + 1] == '\0'))
		// {
		// 	temp[j] = ft_calloc(sizeof(char), 2);
		// 	temp[j] = ft_strdup("$");
		// }
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
			break;
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
	char 	*new;
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
			new = getenv(venv);
			if (new == NULL)
			{
				new = "";
				return (new);
			}
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

char	*ft_join_array(char *temp[256])
{
	int		i;
	char	*joined;

	joined = "";
	i = 0;
	while (temp[i] != NULL)
	{
		joined = ft_strjoin(joined, temp[i]);
		i++;
	}
	return (joined);
}

