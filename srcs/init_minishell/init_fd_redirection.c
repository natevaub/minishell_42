#include "../../includes/minishell.h"

extern t_global	global;

int	ft_error_red_file(char	*file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
}

int	ft_get_infile_fd(t_tok **tk)
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
	// if (fd == -1)
	// 	global.last_exit_status = ft_open_failed((*tk)->word);
	else
		global.last_exit_status = 0;
	return (fd);
}


int	ft_get_outfile_fd(t_tok **tk)
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
		fd = open((*tk)->word, O_CREAT, O_TRUNC, O_WRONLY, 0644);
		printf("FD = %d\n", fd);
	}
	global.last_exit_status = 0;
	return (fd);
}


int	ft_get_append_outfile_fd(t_tok **tk)
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
		fd = open((*tk)->word, O_CREAT, O_APPEND, O_WRONLY, 0644);
	global.last_exit_status = 0;
	return (fd);

}
void	ft_open_files_redirection(t_tok **tk, t_cmd *cmd)
{
	printf("In ft_open_red : Tk = %s --- \n", (*tk)->word);
	if (ft_strcmp((*tk)->word, D_INFILE) == 0)
	{
		cmd->read = ft_get_infile_fd(tk);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;

	}
	else if (ft_strcmp((*tk)->word, D_OUTFILE) == 0)
	{
		printf("Tk = %s --- Tk Next = %s\n", (*tk)->word, (*tk)->next->word);
		cmd->write = ft_get_outfile_fd(tk);
		if ((*tk) != NULL)
		{
			// printf("Tk = %s --- Tk Next = %s\n", (*tk)->word, (*tk)->next->word);
			((*tk)) = (*tk)->next;
		}
			
	}
	else if (ft_strcmp((*tk)->word, D_APPEND) == 0)
	{
		cmd->write = ft_get_append_outfile_fd(tk);
		if ((*tk) != NULL)
			((*tk)) = (*tk)->next;
	}
}
