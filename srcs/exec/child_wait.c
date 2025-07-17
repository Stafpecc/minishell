/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:43:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 13:26:43 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static void	child_signal(int status, t_utils *utils)
{
	int	sig;

	if (WIFEXITED(status))
		utils->last_return = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		utils->last_return = (128 + sig);
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		if (sig == SIGINT)
			write(STDERR_FILENO, "\n", 1);
	}
}

// main process wait once last child
// or sigint sent update the last return
// set back signals, close what need to be closed
// and EXIT_SUCCESS
// to hold the last return value of the last child
// then return 0 on success
int	wait_for_children_and_cleanup(t_utils *utils, int status, int *pipe_fd,
		pid_t child)
{
	int	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == child)
			child_signal(status, utils);
		pid = wait(&status);
	}
	if (close_and_set_none(utils->previous_pipes, pipe_fd) == -1)
		return (MALLOC_ERROR);
	return (EXIT_SUCCESS);
}
