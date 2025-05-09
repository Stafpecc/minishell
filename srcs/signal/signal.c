

#include "signal_handler.h"
#include "minishell.h"

static void ctrl_c(void)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

//TOFIX?LDEV : is the function name right?
// the subject tell us that ctrlbackslash shouldnt do anything
static void ctrl_backslash() 
{
	(void)0;
}

void sig_handler(int sig)
{
	if (sig == SIGINT)
		ctrl_c();
	if (sig == SIGQUIT)
		ctrl_backslash();
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

