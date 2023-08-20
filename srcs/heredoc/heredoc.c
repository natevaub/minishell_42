#include "../includes/minishell.h"

int	ft_heredoc(t_minishell *shell)
{
	char			*content;
	char			*del;
	t_linked_list	*node;

	if (ft_heredoc_detected(shell) == 1)
	{
		del = ft_get_heredoc_eof(shell);
		if (ft_eof_quoted(del) == 1)
		{
			DBG("EOF Quoted\n");
			del = ft_strtrim(del, "\"'");
			node = ft_store_heredoc_content(del);
			content = ft_list_to_char(node);
			DBG(content);
			ft_write_to_temp_file(content);
		}
		else
		{
			DBG("EOF Unquoted\n");
			node = ft_store_heredoc_content(del);
			content = ft_list_to_char_expands(node);
			DBG(content);
			ft_write_to_temp_file(content);
		}
	}
	return (0);
}

int	ft_get_heredoc_temp_fd(t_tok **tk, t_minishell *ms)
{
	int	fd;

	fd = open(".heredoc", O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("Error opening .hereodc file\n");
		exit(EXIT_FAILURE);
	}
	while ((*tk)->next->type != E_STRING)
	{
		*tk = (*tk)->next;
	}
	*tk = (*tk)->next;
	return (fd);
}