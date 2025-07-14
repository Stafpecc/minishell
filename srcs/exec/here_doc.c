/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:48:14 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/14 14:32:33 by stafpec          ###   ########.fr       */
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

static int	readline_loop(int fd, char *delimiter)
{
	char *input;

	while (1)
	{
		input = readline("> ");
		if (g_interrupted)
		{
			g_interrupted = 0;
			free(input);
			return (-130);
		}
		if (!input)
		{
			write(2, "\n", 1);
			return (-1);
		}
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			return (RETURN_SUCCESS);
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
}

int	get_available_heredoc_filename(char *buffer, size_t size)
{
	int			i;
	char		*index;
	const char	*base = ".heredoc";

	i = 0;
	while (i < MAX_HEREDOC_ATTEMPTS)
	{
		if (i == 0)
			ft_strncpy(buffer, ".heredoc.tmp", size);
		else
		{
			index = ft_itoa(i);
			if (!index)
				return (-1);
			ft_strncpy(buffer, base, size);
			ft_strncat(buffer, index, size - ft_strlen(buffer) - 1);
			ft_strncat(buffer, ".tmp", size - ft_strlen(buffer) - 1);
			free(index);
		}
		if (access(buffer, F_OK) != 0)
			return (0);
		i++;
	}
	return (-1);
}

// I create .heredoc.tmp with open and associate its fd into fd, I secure it
// we go to readline_heredoc that should return us 0 if everything went well
// inside of it we gonna fill .heredoc.tmp with user's input(s)
// once outside we close close fd and do a new open that is RDONLY this time
// if fail return -1, else unlink (fd would still work even with unlink)
// to remove .heredoc.tmp from the directory then we return the FD that
// should be used in dup to get the content as the read content!

int readline_heredoc(int fd, char *delimiter)
{
	struct sigaction	sa_new;
	struct sigaction	sa_old;
	int					return_value;

	g_interrupted = 0;

	sa_new.sa_handler = sig_handler;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	return_value = readline_loop(fd, delimiter);
	sigaction(SIGINT, &sa_old, NULL);
	set_signals();

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
	int		fd;
	int		return_value;
	char	tmpfile[64];

	if (get_available_heredoc_filename(tmpfile, sizeof(tmpfile)) == -1)
		return (-1);
	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	return_value = readline_heredoc(fd, delimiter);
	if (return_value == -1 || return_value == -130)
	{
		unlink(tmpfile);
		close(fd);
		return (return_value);
	}
	close(fd);
	fd = open(tmpfile, O_RDONLY);
	if (fd < 0)
		return (-1);
	unlink(tmpfile);
	return (fd);
}
