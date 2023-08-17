#include "../../includes/minishell.h"

extern g_global	global;

int	ft_error_red_file(char	*file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
}

void	ft_open_failed(char *str, t_minishell *ms)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ms->last_exit_status = 1;
}

int	ft_get_infile_fd(t_tok **tk, t_minishell *ms)
{
	int	fd;


	fd = 0;
	(*tk) = (*tk)->next;
	if ((*tk) == NULL)
		return (fd);
	while ((*tk)->type == E_SPACE)
	{
		if ((*tk)->next == NULL)
		{
			(*tk) = (*tk)->next;
			break ;
		}
		(*tk) = (*tk)->next;
	}
	if ((*tk) != NULL)
		fd = open((*tk)->word, O_RDONLY);
	if (fd == -1)
		ft_open_failed((*tk)->word, ms);							//need to create a function for "infile: No such file or directory"
	else
		ms->last_exit_status = 0;
	return (fd);
}


int	ft_get_outfile_fd(t_tok **tk, t_minishell *ms)
{
	int	fd;


	fd = 1;
	(*tk) = (*tk)->next;
	if (*tk == NULL)
		return (fd);
	while ((*tk)->type == E_SPACE)
	{
		printf("E_SPACE Tk Word = %s\n", (*tk)->word);
		if ((*tk)->next == NULL)
		{
			(*tk) = (*tk)->next;
			break ;
		}

		(*tk) = (*tk)->next;
	}
	if ((*tk) != NULL)
	{
		printf("Open Tk Word = %s\n", (*tk)->word);
		fd = open((*tk)->word, O_CREAT | O_TRUNC | O_RDWR, 0666);
		printf("FD = %d\n", fd);
	}
	ms->last_exit_status = 0;
	return (fd);
}


int	ft_get_append_outfile_fd(t_tok **tk, t_minishell *ms)
{
	int	fd;


	fd = 1;
	(*tk) = (*tk)->next;
	if (*tk == NULL)
		return (fd);
	while ((*tk)->type == E_SPACE)
	{
		if ((*tk)->next == NULL)
		{
			(*tk) = (*tk)->next;
			break ;
		}
		(*tk) = (*tk)->next;
	}
	if ((*tk) != NULL)
		fd = open((*tk)->word, O_CREAT | O_APPEND | O_RDWR, 0644);
	ms->last_exit_status = 0;
	return (fd);

}
void	ft_open_files_redirection(t_tok **tk, t_cmd *cmd, t_minishell *ms)
{
	if (ft_strcmp((*tk)->word, D_INFILE) == 0)
	{
		cmd->read = ft_get_infile_fd(tk, ms);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;

	}
	else if (ft_strcmp((*tk)->word, D_OUTFILE) == 0)
	{
		cmd->write = ft_get_outfile_fd(tk, ms);
		if ((*tk) != NULL)
		{
			((*tk)) = (*tk)->next;
		}

	}
	else if (ft_strcmp((*tk)->word, D_APPEND) == 0)
	{
		cmd->write = ft_get_append_outfile_fd(tk, ms);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
}
