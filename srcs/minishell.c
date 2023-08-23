/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/23 14:57:37 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

int	main(int ac, char **av, char **envp)
{
	t_minishell			shell;
	char				*prompt;

	ft_init_minishell(&shell, envp, ac, av);
	while (1)
	{
		ft_init_signals(signal_exec_handler);
		prompt = ft_output_command_line();
		if (prompt == NULL)
			exit(0);
		add_history(prompt);
		ft_parsing(&shell, prompt);
		ft_init_signals(signal_child_handler);
		if (shell.syntax == 0 && shell.last_exit_status == 0)
		{
			if (ft_count_cmds(shell.cmd) < 2)
			{
				// DBG("in exec no pipe");
				ft_exec_no_pipe(&shell, envp);
			}
			else
			{
				// DBG("in exec pipe");
				ft_pipeline_execution(&shell, envp);
			}
		}
		ft_free_parsing(&shell, prompt);
	}
	ft_finish_minishell(&shell);
	return (0);
}

		// ft_print_tokens(shell.token);
		// ft_print_cmds(shell.cmd);