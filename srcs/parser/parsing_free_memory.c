#include "../includes/minishell.h"

void	ft_free_token(t_minishell *shell)
{
	t_tok	*curr;
	t_tok	*next;

	curr = shell->token;
	next = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->word);
		free(curr);
		curr = next;
	}
	shell->token = NULL;

}

void	ft_free_cmd(t_minishell *shell)
{
	t_lcmd	*curr;
	t_lcmd	*next;
	int		i;

	curr = shell->cmd;
	next = NULL;
	while(curr != NULL)
	{
		i = 0;
		next = curr->next;
		// while (curr->option[i]!= NULL)
		// {
		// 	free(curr->option[i]);
		// 	i++;
		// }
		free(curr->option);
		free(curr);
		curr = next;
	}
	shell->cmd = NULL;
}

void	ft_free_parsing(t_minishell *shell)
{
	ft_free_token(shell);
	ft_free_cmd(shell);
}