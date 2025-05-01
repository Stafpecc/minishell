#ifndef MINISIGNAL_H
# define MINISIGNAL_H

# include <signal.h>
# include <unistd.h>

void	sig_handler(int sig);
void	set_signals(void);

#endif