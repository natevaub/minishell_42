/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/08/14 10:58:23 by nvaubien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* function int sigaction(int signum, const struct sigaction *newact, struct sigaction *oldact);
takes two struct sigaction as parameters

struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};*/

/*Ctrl-C (in older Unixes, DEL) sends an INT signal ("interrupt", SIGINT); by default, this causes the process to terminate.
Ctrl-Z sends a TSTP signal ("terminal stop", SIGTSTP); by default, this causes the process to suspend execution.[4]
Ctrl-\ sends a QUIT signal (SIGQUIT); by default, this causes the process to terminate and dump core.
Ctrl-D does not send any signal, it rather sends an input to the terminal, which is EOF.

in minishell:
Ctrl-C = display a new line
Ctrl-D = exit the program
Ctrl-\ = do nothing*/

// void	init_signals(void)
// {
// 	struct sigaction	s;

// 	s.sa_handler = &(signal_handler);
// 	sigemptyset(&s.sa_mask);
// 	s.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &s, NULL);
// 	sigaction(SIGQUIT, &s, NULL);
// }

void	ft_init_signals(void (*handle_signals)(int))
{
	struct sigaction	sa;
	struct termios		termios;

	if ((tcgetattr(STDIN_FILENO, &termios)) == -1)
		exit(EXIT_FAILURE);
	termios.c_lflag &= ~(ECHOCTL);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &termios)) == -1)
		exit(EXIT_FAILURE);
	sa.sa_handler = handle_signals;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGQUIT");
}

void	signal_prompt_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// global.last_exit_status;
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("  ", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_exec_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("  ", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("  ", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}