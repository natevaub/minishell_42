/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/29 17:45:04 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//On success, zero is returned.  On error, -1 is returned, and
//errno is set to indicate the error.
int	cmd_cd(t_lcmd *cmd, t_minishell *ms)
{
	char	*path;

	if (cmd->option[2])
	{
		// ft_putstr_fd("minishell: ", 2);
		// ft_putstr_fd(cmd->option[0], 2);
		// ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
		return (EXIT_SUCCESS);
	}
	if (!(cmd->option[1]))
		path = ft_strdup(get_value(ms->copy_env, "HOME"));
	else
		path = ft_strdup(cmd->option[1]);
	if (chdir(path) < 0)
	{
		free (path);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->option[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd->option[1], 2);
		ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	free(path);
	return (EXIT_SUCCESS);
}

//PWD WITH NO OPTIONS
/*The pwd utility writes the absolute pathname of the current working directory
to the standard output.*/
int	cmd_pwd(t_lcmd *cmd)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return (errno);
	ft_putstr_fd(tmp, cmd->fd_write);
	ft_putchar_fd('\n', cmd->fd_write);
	free(tmp);
	return (EXIT_SUCCESS);
}
