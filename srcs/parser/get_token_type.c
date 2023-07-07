#include "../includes/minishell.h"

int	ft_is_red(char *prompt)
{
	if (ft_strcmp(prompt, D_INFILE) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_OUTFILE) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_HEREDOC) == 0)
		return (1);
	else if (ft_strcmp(prompt, D_APPEND) == 0)
		return (1);
	return (0);
}

int	ft_red_type(char *prompt)
{
	if (ft_strcmp(prompt, D_INFILE) == 0)
		return (E_INFILE);
	else if (ft_strcmp(prompt, D_OUTFILE) == 0)
		return (E_OUTFILE);
	else if (ft_strcmp(prompt, D_HEREDOC) == 0)
		return (E_HEREDOC);
	else if (ft_strcmp(prompt, D_APPEND) == 0)
		return (E_APPEND);
	return (E_NORED);
}

int	ft_is_pipe(char *prompt)
{
	if (ft_strcmp(prompt, D_PIPE) == 0)
		return (1);
	return (0);
}

int	ft_is_space(char *prompt)
{
	if (*prompt == ' ' || *prompt == '\t')
		return (1);
	return (0);
}
