#include "../includes/minishell.h"

char	*ft_remove_tk_quote(char *word)
{
	char	*trimmed;
	char	c;

	c = word[0];
	trimmed = ft_strtrim(word, &c);
	free(word);
	return (trimmed);
}

void	ft_trim_quote(t_minishell *shell)
{
	t_tok *tk;

	tk = shell->token;
	while (tk != NULL)
	{
		if (tk->quote != E_NONE)
		{
			tk->word = ft_remove_tk_quote(tk->word);
		}
		tk = tk->next;
	}
}