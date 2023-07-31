/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_builtin_others.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:38:36 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/05 17:08:20 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_global	global;

//CD WITH ONLY A RELATIVE OR ABSOLUTE PATH
/*The cd command in Linux is known as the change directory command.
It is used to move efficiently from the current working
directory to different directories in our System.*/

//On success, zero is returned.  On error, -1 is returned, and
//errno is set to indicate the error.
int	cmd_cd(t_minishell *ms)
{
	char	*path;

	if (!(ms->cmd->option[1]))
		path = ft_strdup(get_value(global.copy_env, "HOME"));
	else
		path = ft_strdup(ms->cmd->option[1]);
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
int	cmd_pwd(t_minishell *ms)
{
	if (getcwd(NULL, 0) == NULL)
		return (errno);
	ft_putstr_fd(getcwd(NULL, 0), ms->cmd->fd_write);								//adjust fd if redirection
	ft_putchar_fd('\n', ms->cmd->fd_write);
	return (EXIT_SUCCESS);
}
