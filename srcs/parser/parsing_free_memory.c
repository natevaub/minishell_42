#include "../../includes/minishell.h"

void	ft_free_token(t_minishell **shell)
{
	t_tok	*curr;
	t_tok	*next;

	curr = (*shell)->token;
	next = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->word)
			free(curr->word);
		if (curr)
			free(curr);
		curr = next;
	}
	(*shell)->token = NULL;

}

void	ft_free_cmd(t_minishell *shell)
{
	// printf("In ft free cmd\n");
	t_lcmd	*curr;
	t_lcmd	*next;
	int		i;

	curr = (shell)->cmd;
	// printf("cmd: %s", (shell)->cmd->cmd);
	next = NULL;
	// printf("step 1\n");
	if (curr->fd_read != 0)
	{
		close(curr->fd_read);
	}
	// printf("step 2\n");
	while(curr != NULL)
	{
		i = 0;
		next = curr->next;
		// while (curr->option[i]!= NULL)								//check why this gives error: pointer freed was not allocated
		// {
		// 	free(curr->option[i]);
		// 	i++;
		// }
		// printf("curr->option[0]: %s", curr->option[0]);
		if (curr->option)
			free(curr->option);
		// free_two_dimension_array(curr->option);
		// printf("step 3\n");
		if (curr->next == NULL && curr->fd_write != 1)
		{
			close(curr->fd_write);
		}
		// printf("step 4\n");
		if (curr)
			free(curr);
		// printf("step 5\n");
		curr = next;
	}
	(shell)->cmd = NULL;
	// printf("step 6\n");
}

void	ft_free_parsing(t_minishell *shell)
{
	ft_free_cmd(shell);
	ft_free_token(&shell);

}