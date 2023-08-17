#include "../../includes/minishell.h"

extern t_global	global;

void	ft_init_minishell(t_minishell *shell, char **env)
{
	*shell = (t_minishell){};
	global.copy_env = new_env_list(env);
	global.last_exit_status = EXIT_SUCCESS;
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
	DBG("Inits cmds 1");
	while ((*tokens) != NULL)
	{
		DBG((*tokens)->word);
		if ((*tokens)->type == E_REDIRECTION)
		{
			DBG("Inits cmds 2");
			ft_open_files_redirection(tokens, cmd);
		}
		else if ((*tokens)->type == E_STRING)
		{
			cmd->option = ft_store_cmd_options(tokens, cmd);
			DBG("Inits cmds 3");
		}
		else if ((*tokens)->type == E_PIPE)
		{
			(*tokens) = (*tokens)->next;
			DBG("Inits cmds 4");
			break ;
		}
		else if ((*tokens) != NULL)
		{
			DBG("Inits cmds 5");
			(*tokens) = (*tokens)->next;
		}
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
			break;
		if ((*tokens) != NULL)
			(*tokens) = (*tokens)->next;
	}
	tmp[i] = NULL;
	options = ft_calloc(sizeof(char *), ft_len_cmd_opt(tmp) + 1);
	options = ft_get_opt(options, tmp);
	return (options);
}
