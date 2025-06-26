/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:21:07 by tarini            #+#    #+#             */
/*   Updated: 2025/06/26 15:48:27 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "minishell.h"

static void	ctrl_c(void)
{
	g_interrupted = 1;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	ctrl_backslash(void)
{
	(void)0;
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		ctrl_c();
	if (sig == SIGQUIT)
		ctrl_backslash();
}

void	set_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
