/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:58:58 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/01 15:16:50 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
#include "../../libft/includes/libft.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

// we init input to NULL, then we get into an infinite while loop
//(can do a bool if norme require it) then we write inside of input
// what the user prompt we secure it, we check if fd and delimiter = the same
// if yes we break the loop to finish the program
// if no we write the content of input with a \n free input set it to null
// then we go back to the start of the loop UNTIL we find the EOF delimiter

volatile sig_atomic_t	g_interrupted = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_interrupted = 1;
	rl_done = 1;
}

static int	readline_loop(int fd, char *delimiter, char *input)
{
	while (1)
	{
		input = readline("> ");
		if (g_interrupted)
		{
			g_interrupted = 0;
			return (-130);
		}
		if (!input)
		{
			write(2, "\n", 1);
			return (-1);
		}
		if (ft_strcmp(input, delimiter) == 0)
			return (RETURN_SUCCESS);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
}

static int	readline_heredoc(int fd, char *delimiter)
{
	char				*input;
	struct sigaction	sa_new;
	struct sigaction	sa_old;
	int					return_value;

	return_value = 0;
	input = NULL;
	g_interrupted = 0;
	sa_new.sa_handler = sigint_handler;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	return_value = readline_loop(fd, delimiter, input);
	sigaction(SIGINT, &sa_old, NULL);
	if (input)
		free(input);
	return (return_value);
}

// I create .heredoc.tmp with open and associate its fd into fd, I secure it
// we go to readline_heredoc that should return us 0 if everything went well
// inside of it we gonna fill .heredoc.tmp with user's input(s)
// once outside we close close fd and do a new open that is RDONLY this time
// if fail return -1, else unlink (fd would still work even with unlink)
// to remove .heredoc.tmp from the directory then we return the FD that
// should be used in dup to get the content as the read content!
// TODO si quelqu'un fait .heredoc.tmp avant de lancer le programme
int	here_doc(char *delimiter)
{
	int	fd;
	int	return_value;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	return_value = readline_heredoc(fd, delimiter);
	if (return_value == -1 || return_value == -130)
	{
		unlink(".heredoc.tmp");
		close(fd);
		return (return_value);
	}
	close(fd);
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd < 0)
		return (-1);
	unlink(".heredoc.tmp");
	return (fd);
}
