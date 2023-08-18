/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/19 00:06:10 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//CD WITH ONLY A RELATIVE OR ABSOLUTE PATH
/*The cd command in Linux is known as the change directory command.
It is used to move efficiently from the current working
directory to different directories in our System.*/

//On success, zero is returned.  On error, -1 is returned, and
//errno is set to indicate the error.
int	cmd_cd(t_lcmd *cmd, t_minishell *ms)
{
	char	*path;

	if (!(cmd->option[1]))
		path = ft_strdup(get_value(ms->copy_env, "HOME"));
	else
		path = ft_strdup(cmd->option[1]);
	if (chdir(path) < 0)
	{
		free (path);
		return (errno);
	}
	free(path);
	return (EXIT_SUCCESS);
}

//PWD WITH NO OPTIONS
/*The pwd utility writes the absolute pathname of the current working directory
to the standard output.*/
int	cmd_pwd(t_lcmd *cmd)
{
	if (getcwd(NULL, 0) == NULL)
		return (errno);
	ft_putstr_fd(getcwd(NULL, 0), cmd->fd_write);								//adjust fd if redirection
	ft_putchar_fd('\n', cmd->fd_write);
	return (EXIT_SUCCESS);
}
