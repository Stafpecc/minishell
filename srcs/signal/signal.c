/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:21:07 by tarini            #+#    #+#             */
/*   Updated: 2025/05/01 18:26:26 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "minishell.h"

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("",0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void set_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL); 
	signal(SIGQUIT, SIG_IGN);
}