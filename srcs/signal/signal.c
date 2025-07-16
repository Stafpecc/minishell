/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:21:07 by tarini            #+#    #+#             */
/*   Updated: 2025/07/16 16:06:48 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "minishell.h"
#include "../../libft/includes/libft.h"

volatile sig_atomic_t	g_interrupted = 0;

static void	ctrl_c(void)
{
	g_interrupted = 1;
	if (rl_readline_state & RL_STATE_COMPLETING)
		rl_pending_input = 'n';
	rl_replace_line("", 0);
	rl_done = 1;
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
