/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/29 22:56:57 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_signals(void (*handle_signals)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handle_signals;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGQUIT");
	else
		g_status = 0;
}

void	ft_set_termios(t_minishell *ms)
{
	struct termios	termios_new;

	if ((tcgetattr(STDIN_FILENO, &ms->termios_default)) == -1)
		exit(EXIT_FAILURE);
	termios_new = ms->termios_default;
	termios_new.c_lflag &= ~(ECHOCTL);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &termios_new)) == -1)
		exit(EXIT_FAILURE);
}

void	ft_unset_termios(t_minishell *ms)
{
		if ((tcsetattr(STDIN_FILENO, TCSANOW, &ms->termios_default)) == -1)
			exit(EXIT_FAILURE);
}

void	ft_init_hd_signals(void (*handle_signals)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handle_signals;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT");
	signal(SIGQUIT, SIG_IGN);
}

void	signal_child_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("^C\n", STDOUT_FILENO);
		g_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: ", STDOUT_FILENO);
		ft_putnbr_fd(SIGQUIT, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_status = 131;
	}
}

void	signal_exec_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_status = 1;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_output_command_line();
		rl_on_new_line();
		rl_redisplay();
		g_status = 1;
	}
}
