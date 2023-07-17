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
	t_lcmd *test;
	int			i;
	int			j;

	i = 0;
	j = 1;
	test = cmd;
	printf("--- PARSING TOKEN -> ----\n");
	while (test != NULL)
	{
		printf(" --- cmd[%d] ---\n", j++);
		printf("[%s] <- cmd\n", test->cmd);
		if (test->cmd != NULL)
		{
			while (test->option[i] != NULL)
			{
				printf("[%s] <- option[%d]\n", test->option[i], i);
				i++;
			}
		}
		i = 0;
		printf("[%d] <- fd_read\n", test->fd_read);
		printf("[%d] <- fd_write\n", test->fd_write);
		test = test->next;
	}
}