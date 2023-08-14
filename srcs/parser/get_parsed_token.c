#include "../includes/minishell.h"

void	ft_parse_token(t_minishell *shell)
{
	t_tok	*start;
	t_tok	*parse;

	start = shell->token;
	parse = shell->token;
	while (parse != NULL)
	{
		if (!shell->cmd)
		{
			shell->cmd = ft_newlst_cmd(ft_init_cmds(&parse));
		}
		else
		{
			ft_lstadd_back_cmd(&shell->cmd,
				ft_newlst_cmd(ft_init_cmds(&parse)));
		}
	}
	shell->token = start;
}

void	ft_parsing(t_minishell *shell, char *prompt)
{
	int	err;

	shell->syntax = 0;
	ft_tokenize_prompt(shell, prompt);
	if (DEBUG) ft_print_tokens(shell->token);
	ft_heredoc(shell);
	printf("After Here Doc\n");
	// exit(0);
	err = 0;
	if (shell->syntax == 0)
	{
		ft_expand_token(shell);
		if (ft_syntax_checker(shell) == 0)
		{
			ft_trim_quote(shell);
			err = ft_join_tk(shell->token);
			ft_parse_token(shell);
			if (DEBUG) ft_print_tokens(shell->token);
			if (DEBUG) ft_print_cmds(shell->cmd);
		}
	}
}