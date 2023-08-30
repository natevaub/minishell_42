/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:57:28 by nvaubien          #+#    #+#             */
/*   Updated: 2023/08/30 17:55:48 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_minishell(t_minishell *shell, char **env, int ac, char **av)
{
	struct termios	termios_new;

	(void) av;
	(void) ac;
	*shell = (t_minishell){};
	shell->copy_env = new_env_list(env);
	shell->last_exit_status = EXIT_SUCCESS;
	if ((tcgetattr(STDIN_FILENO, &shell->termios_default)) == -1)
		exit(EXIT_FAILURE);
	termios_new = shell->termios_default;
	termios_new.c_lflag &= ~(ECHOCTL);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &termios_new)) == -1)
		exit(EXIT_FAILURE);
	g_status = 0;
	shell->heredoc = 0;
}

char	**ft_get_opt(char **option, char **tmp)
{
	size_t	i;

	i = 0;
	while (tmp[i] != NULL)
	{
		option[i] = tmp[i];
		i++;
	}
	return (option);
}

int	ft_len_cmd_opt(char **options)
{
	size_t	i;

	i = 0;
	while (options[i] != NULL)
		i++;
	return (i);
}

t_cmd	*ft_init_cmds(t_tok **tokens)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	*cmd = (t_cmd){};
	cmd->read = 0;
	cmd->write = 1;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->type == E_REDIRECTION)
		{
			ft_open_files_redirection(tokens, cmd);
		}
		else if ((*tokens)->type == E_STRING)
			cmd->option = ft_store_cmd_options(tokens, cmd);
		else if ((*tokens)->type == E_PIPE)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		else if ((*tokens) != NULL)
			(*tokens) = (*tokens)->next;
	}
	return (cmd);
}

char	**ft_store_cmd_options(t_tok **tokens, t_cmd *cmd)
{
	char	*tmp[1024];
	char	**options;
	int		i;

	i = 1;
	cmd->cmd = (*tokens)->word;
	tmp[0] = cmd->cmd;
	(*tokens) = (*tokens)->next;
	while ((*tokens) != NULL)
	{
		if ((*tokens)->type == E_STRING)
		{
			tmp[i] = (*tokens)->word;
			i++;
		}
		else if ((*tokens)->type == E_REDIRECTION || (*tokens)->type == E_PIPE)
			break ;
		if ((*tokens) != NULL)
			(*tokens) = (*tokens)->next;
	}
	tmp[i] = NULL;
	options = ft_calloc(sizeof(char *), ft_len_cmd_opt(tmp) + 1);
	options = ft_get_opt(options, tmp);
	return (options);
}
