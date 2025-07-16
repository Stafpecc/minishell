/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:43:54 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/16 17:51:02 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

// once the childs are created the parent
// is gonna close everything that need to be closed here
// then it will wait at waitpid and also update last_return
// to hold the last return value of the last child
// then return 0 on success
int	wait_for_children_and_cleanup(t_utils *utils, int status,
		int *pipe_fd, pid_t child)
{
	int	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		ft_printfd("je passe ici?\n");
		printf("child = %d\n", child);
		printf("pid = %d\n", pid);
		if (pid == child)
			child_signal(status, utils);
		pid = wait(&status);
	}
	if (close_and_set_none(utils->previous_pipes, pipe_fd) == -1)
		return (MALLOC_ERROR);
	ft_printfd("last_return = %d\n", utils->last_return);
	return (EXIT_SUCCESS);
}
