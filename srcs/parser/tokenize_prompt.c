// #include "../includes/minishell.h"

// void	ft_tokenize_prompt(t_minishell *global, char *prompt)
// {
// 	t_list_token	*tk;

// 	while (*prompt == ' ' || *prompt == '\t')
// 		prompt++;
// 	tk = ft_newlst_token(ft_get_tk(&prompt));
// 	global->token = tk;
// 	while (*prompt != '\0')
// 	{
// 	}
// }

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

// int	ft_get_tk_type(char *str)
// {
// 	if (ft_is_red(str) == 1)
// 		return (E_REDIRECTION);
// 	else if (ft_is_pipe(str))
// 		return (E_PIPE);
// 	else if (ft_is_space(str))
// 		return (E_SPACE);
// }