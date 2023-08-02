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
		free(curr->word);
		free(curr);
		curr = next;
	}
	(*shell)->token = NULL;

}

void	ft_free_cmd(t_minishell **shell)
{
	t_lcmd	*curr;
	t_lcmd	*next;
	int		i;

	curr = (*shell)->cmd;
	next = NULL;
	if (curr->fd_read != 0)
	{
		close(curr->fd_read);
	}
	while(curr != NULL)
	{
		i = 0;
		next = curr->next;
		// while (curr->option[i]!= NULL)								//check why this gives error: pointer freed was not allocated
		// {
		// 	free(curr->option[i]);
		// 	i++;
		// }
		free(curr->option);
		if (curr->next == NULL && curr->fd_write != 1)
		{
			close(curr->fd_write);
		}
		free(curr);
		curr = next;
	}
	(*shell)->cmd = NULL;
}

void	ft_free_parsing(t_minishell *shell)
{
	ft_free_cmd(&shell);
	ft_free_token(&shell);

}