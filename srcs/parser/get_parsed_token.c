#include "../includes/minishell.h"

void	ft_parse_token(t_minishell *shell)
{
	t_tok	*start;
	t_tok	*parse;

	start = shell->token;
	parse = shell->token;
	DBG("Shell Token :");
	DBG(shell->token->word);
	while (parse != NULL)
	{
		if (!shell->cmd)
		{
			DBG("7");
			shell->cmd = ft_newlst_cmd(ft_init_cmds(&parse));
		}
		else
		{
			DBG("8");
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
	DBG("1");
	ft_heredoc(shell);
	DBG("2");
	err = 0;
	if (shell->syntax == 0)
	{
		DBG("3");
		ft_expand_token(shell);
		if (ft_syntax_checker(shell) == 0)
		{
			DBG("4");
			ft_trim_quote(shell);
			DBG("5");
			err = ft_join_tk(shell->token);
			DBG("6");
			ft_parse_token(shell);
			DBG("9");
			if (DEBUG) ft_print_tokens(shell->token);
			if (DEBUG) ft_print_cmds(shell->cmd);
		}
	}
}