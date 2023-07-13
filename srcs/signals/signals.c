/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:04:19 by ckarl             #+#    #+#             */
/*   Updated: 2023/07/11 14:57:34 by ckarl            ###   ########.fr       */
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

void	init_signals(struct sigaction *s)
{
	s->sa_handler = &(signal_handler);
	sigemptyset(&s->sa_mask);
	s->sa_flags = SA_RESTART;
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text				//cannot find it in readline header
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		SIG_IGN;					//should do nothing
}