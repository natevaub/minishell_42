#include "../includes/minishell.h"

char	*ft_remove_tk_quote(char *word)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	new = ft_calloc(sizeof(char), ft_strlen(*word) + 1 - 2);
	printf("Len of new = %zu\n", ft_strlen(*word));
	if (!new)
		exit(printf("Malloc Error\n") + 247);
	while (word[i] != '\0')
	{

	}
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