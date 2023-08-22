#include "../../includes/minishell.h"

void	ft_free_token(t_minishell *shell)
{
	t_tok	*curr;
	t_tok	*next;

	curr = shell->token;
	next = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		// if (curr->word)
		// 	free(curr->word);
		if (curr)
			free(curr);
		curr = next;
	}
	shell->token = NULL;

}

void	ft_free_cmd(t_minishell *shell)
{
	// printf("In ft free cmd\n");
	t_lcmd	*temp_cmd;
	t_lcmd	*next;

	temp_cmd = shell->cmd;
	next = NULL;
	while(temp_cmd != NULL)
	{
		next = temp_cmd->next;
		if (temp_cmd->option)
			free(temp_cmd->option);
		if (temp_cmd->cmd)
			free(temp_cmd->cmd);
		if (temp_cmd)
			free(temp_cmd);
		temp_cmd = next;
	}
	shell->cmd = NULL;
}

void	ft_free_parsing(t_minishell *shell)
{
	if (shell->cmd)
		ft_free_cmd(shell);
	if (shell->token)
		ft_free_token(shell);
	if (shell->heredoc == 1)
	{
		unlink(".heredoc");
		shell->heredoc = 0;
	}
}