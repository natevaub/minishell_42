#include "../includes/minishell.h"

char	*ft_get_heredoc_eof_util(t_tok *tok)
{
	char	*eof;
	t_tok	*start;

	start = tok;
	while (tok->type == E_SPACE)
	{
		tok = tok->next;
	}
	if (tok->type == E_STRING)
	{
		eof = ft_strdup(tok->word);
	}
	printf("EOF = %s\n", eof);
	tok = start;
	return (eof);
}

char	*ft_get_heredoc_eof(t_minishell *shell)
{
	t_tok	*start;
	char	*eof;

	start = shell->token;
	while (ft_strcmp(shell->token->word, D_HEREDOC) != 0)
	{
		shell->token = shell->token->next;
	}
	shell->token = shell->token->next;
	eof = ft_get_heredoc_eof_util(shell->token);
	shell->token = start;
	return (eof);
}

int	ft_heredoc_detected(t_minishell *shell)
{
	t_tok	*start;

	start = shell->token;
	while (shell->token != NULL)
	{
		if (ft_strcmp(shell->token->word, D_HEREDOC) == 0)
		{
			shell->token = start;
			return (1);
		}
		shell->token = shell->token->next;
	}
	shell->token = start;
	return (0);
}

bool	ft_eof_quoted(char *eof)
{
	int	i;

	i = 0;
	while (i < ft_strlen(eof))
	{
		if (eof[i] == '\'' || eof[i] == '"')
			return (true);
		i++;
	}
	return (false);
}