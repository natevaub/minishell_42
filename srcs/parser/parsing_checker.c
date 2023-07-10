#include "../includes/minishell.h"

void	ft_printlist_tk(t_tok *global)
{
	t_tok	*test;
	int		i;

	test = global;
	i = 0;
	while (test != NULL)
	{
		printf("Token[%d] - Word is \" %s \"\n", i, test->word);
		printf("Token[%d] - Type is \" %d \"\n", i, test->type);
		printf("Token[%d] - Red is \" %d \"\n", i, test->red);
		printf("Token[%d] - Quote is \" %d \"\n", i, test->quote);
		test = test->next;
		i++;
	}
}