/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/22 16:34:20 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

<<<<<<< HEAD
int	g_status;

int main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;
	(void)				ac;
	(void)				av;
	ft_init_minishell(&shell, envp);
=======
int	main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;

	ft_init_minishell(&shell, envp, av, ac);
>>>>>>> 6446f01d8b15cddf622c3a70a205460fa72c14a8
	while (1)
	{
		ft_init_signals(signal_exec_handler);
		prompt = ft_output_command_line();
		ft_init_signals(signal_child_handler);
		if (prompt == NULL)
			exit(0);
		if (prompt)
			add_history(prompt);
		ft_parsing(&shell, prompt);
		if (shell.syntax == 0 && shell.last_exit_status != 1)
		{
			if (ft_count_cmds(shell.cmd) < 2)
				ft_exec_no_pipe(&shell, envp);
			else
				ft_pipeline_execution(&shell, envp);
		}
		ft_free_parsing(&shell, prompt);
	}
	ft_finish_minishell(&shell);
	return (0);
}
