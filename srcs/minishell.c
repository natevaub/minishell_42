/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/30 19:53:35 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

int	main(int ac, char **av, char **envp)
{
	t_minishell		shell;
	char			*prompt;

	ft_init_minishell(&shell, envp, ac, av);
	while (1)
	{
		ft_init_signals(signal_exec_handler);
		prompt = ft_output_command_line();
		if (prompt == NULL)
			exit(0);
		if (prompt)
			add_history(prompt);
		ft_parsing(&shell, prompt);
		if (shell.syntax == 0)
		{
			ft_init_signals(signal_child_handler);
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
