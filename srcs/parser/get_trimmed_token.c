#include "../includes/minishell.h"

char	*ft_remove_tk_quote(char **prompt)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	new = ft_calloc(sizeof(char), ft_strlen(*prompt) + 1);
	printf("Len of prompt = %zu\n", ft_strlen(*prompt));
	return (new);
}

void	ft_trim_quote(t_minishell *shell)
{
	t_tok *tk;

	tk = shell->token;
	while (tk != NULL)
	{
		if (tk->quote != E_NONE)
			tk->word = ft_remove_tk_quote(&tk->word);
		tk = tk->next;
	}
}