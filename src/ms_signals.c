/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsala <jsala@student.42barcelona.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:53:52 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/18 10:48:50 by jsala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void) sig;
	if (write(2, "\n", 1) == -1)
	{
		printf("Error writing on stdout");
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	reset_sighandlers(void)
{
	if (signal(SIGQUIT, SIG_DFL))
		return (1);
	if (signal(SIGINT, SIG_DFL))
		return (1);
	return (0);
}

int	event_rl(void)
{
	return (EXIT_SUCCESS);
}

// Ctrl-C SIGINT
// Ctrl-D is not a signal, just an EOF
// Ctrl-\ SIGQUIT -> does nothing
int	set_sighandlers(void)
{
	rl_catch_signals = 0;
	rl_event_hook = event_rl;
	if (signal(SIGQUIT, SIG_IGN))
		return (1);
	if (signal(SIGINT, sigint_handler))
		return (1);
	return (0);
}
