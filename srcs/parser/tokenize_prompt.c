// #include "../includes/minishell.h"

void	ft_tokenize_prompt(t_minishell *global, char *prompt)
{
	t_tok	*tk;

	while (*prompt == ' ' || *prompt == '\t')
		prompt++;
	tk = ft_newlst_token(ft_get_tk(&prompt));
	global->token = tk;
	while (*prompt != '\0')
	{
		ft_lstadd_back_token(&global->token, ft_newlst_token(ft_get_tk(&prompt)));
	}
}


// char	*ft_get_tk(char **prompt)
// {
// 	char	*ret;

// 	ret = NULL;
// 	if (**prompt == '<' || **prompt == '>' || **prompt == '|')
// 		ret = ft_get_word_red(prompt, (char)**prompt);
// 	else if (**prompt == ' ' || **prompt == '\t')
// 		ret = ft_get_word_space(prompt);
// 	else
// 		ret = ft_get_word(prompt);
// 	return (ret);
// }

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

int	ft_get_quoted_tk(char *prompt)
{
	if (prompt[0] == '\'')
		return (E_SINGLE);
	else if (prompt[0] == '\"')
		return (E_DOUBLE);
	return (E_NONE);
}