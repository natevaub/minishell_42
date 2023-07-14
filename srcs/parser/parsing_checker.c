#include "../includes/minishell.h"

void	ft_printlist_tk(t_tok *global)
{
	t_tok	*test;
	int		i;

	test = global;
	i = 0;
	while (test != NULL)
	{
		printf("---	---	---	---	---	---	---	---\n");
		printf("---	Token[%d]	- Word is	\" %s \"	---\n", i, test->word);
		printf("---	Token[%d]	- Type is	\" %d \"		---\n", i, test->type);
		printf("---	Token[%d]	- Red is	\" %d \"		---\n", i, test->red);
		printf("---	Token[%d]	- Quote is	\" %d \"		---\n", i, test->quote);
		printf("---	---	---	---	---	---	---	---\n");
		test = test->next;
		i++;
	}
}

void	ft_print_cmds(t_lcmd *cmd)
{
	t_lcmd	*test;
	int		i;
	int		j;

	i = 0;
	j = 1;
	test = cmd;
	printf("1\n");
	while (test != NULL)
	{
		printf("2\n");
		if (test->cmd != NULL)
		{
			printf("3\n");
			while (test->option[i] != NULL)
			{
				printf("4\n");
				printf("---	---	---	---	---	---	---	---\n");
				printf("---	Option[%d]	-  is	\" %s \"	---\n", i, test->option[i]);
				printf("---	---	---	---	---	---	---	---\n");
				i++;
			}
		}
		i = 0;
		test = test->next;
	}
}