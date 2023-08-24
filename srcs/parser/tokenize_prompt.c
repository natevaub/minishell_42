/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:46:40 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/24 11:59:10 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tokenize_prompt(t_minishell *global, char *prompt)
{
	t_tok	*tk;

	tk = NULL;
	while (*prompt == ' ' || *prompt == '\t')
		prompt++;
	global->token = tk;
	while (*prompt != '\0')
	{
		ft_lstadd_back_token(&global->token, \
			ft_newlst_token(ft_get_tk(&prompt)));
	}
}

int	ft_get_tk_type(char *prompt)
{
	if (ft_is_red(prompt) == 1)
		return (E_REDIRECTION);
	else if (ft_is_pipe(prompt))
		return (E_PIPE);
	else if (ft_is_space(prompt))
		return (E_SPACE);
	else
		return (E_STRING);
}

char	*ft_get_tk(char **prompt)
{
	char	*ret;

	ret = NULL;
	if (**prompt == '<' || **prompt == '>' || **prompt == '|')
		ret = ft_get_word_red(prompt, (char)**prompt);
	else if (**prompt == ' ' || **prompt == '\t')
		ret = ft_get_word_space(prompt);
	else if (**prompt == '\'' || **prompt == '"')
		ret = ft_get_word_quote(prompt, **prompt);
	else
		ret = ft_get_word(prompt);
	return (ret);
}

int	ft_get_quoted_tk(char *prompt)
{
	if (prompt[0] == '\'')
		return (E_SINGLE);
	else if (prompt[0] == '\"')
		return (E_DOUBLE);
	return (E_NONE);
}
