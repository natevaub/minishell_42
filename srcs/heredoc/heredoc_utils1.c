#include "../includes/minishell.h"

/* 
	The Goal of this function is to store the character that indicates heredoc to stop
	waiting for user prompt
*/

int	ft_heredoc(t_minishell *shell)
{
	char	*del;
	if (ft_heredoc_detected(shell) == 1)
	{
		del = ft_get_heredoc_eof(shell);
		printf("Del %s\n", del);
		ft_read_until_eof(del);
	}
	return (0);
}

char	*ft_get_heredoc_eof_util(t_tok *tok)
{
	char	*eof;

	while (tok->type == E_SPACE)
	{
		printf("IS_SPACE Detected\n");
		tok = tok->next;
	}
	if (tok->type == E_STRING)
	{
		eof = ft_strdup(tok->word);
	}
	printf("EOF = %s\n", eof);
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
			return (1);
		}
		shell->token = shell->token->next;
	}
	shell->token = start;
	return (0);
}

void	ft_read_until_eof(char *eof)
{
	int		num_line;
	int		i;
	char	*all_lines[MAX_INPUT_LINE];
	char	*line;
	char	*input;
	char	*tmp;
	char	*new_line;

	line = NULL;
	num_line = 0;
	i = 0;
	
	while ((line = readline("> ")) != NULL)
	{
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break;
		}
		if (ft_heredoc_line_got_dollar(line) == true)
		{
			new_line = ft_get_line_with_expand(line);
			DBG(new_line);
		}
		all_lines[num_line] = new_line;
		num_line += 1;
	}
	input = ft_strdup("");
	while (i < num_line)
	{
		tmp = input;
		input = ft_strjoin(tmp, all_lines[i]);
		free(tmp);
		free(all_lines[i]);
		i++;
	}
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

char	*ft_heredoc_expand(char *input)
{
	char	*new;

	return (NULL);
}