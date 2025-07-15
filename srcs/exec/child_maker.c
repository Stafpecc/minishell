/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:51:58 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/15 15:10:15 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
#include <stdlib.h>

// once the childs are created the parent
// is gonna close everything that need to be closed here
// then it will wait at waitpid and also update last_return
// to hold the last return value of the last child
// then return 0 on success

int	wait_for_children_and_cleanup(t_utils *utils, int status,
		int *pipe_fd, pid_t child)
{
	int	pid;
	int	sig;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == child)
		{
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
		pid = wait(&status);
	}
	if (close_and_set_none(utils->previous_pipes, pipe_fd) == -1)
		return (MALLOC_ERROR);
	return (EXIT_SUCCESS);
}
// is previous pipe exist if yes is it not the last cmd?
// if both yes we do a new pipe and secure it
// else if we are at the very last cmd we close
// pipe_fd[1](WRITE END) in a secured way and
// it get value -42 for later comparisons (TODO CHECK
// IF BETTER WAY TO HANDLE THAT CASE)
// then return 0 if successful run

int	setup_coming_child_pipes(t_utils *utils, int *pipe_fd, int i)
{
	if (utils->previous_pipes != NONE && i < utils->num_nodes - 1)
	{
		if (pipe(pipe_fd) == -1)
			return (EXIT_FAILURE);
	}
	else if (i == utils->num_nodes - 1 && pipe_fd[1] != NONE)
	{
		if (close(pipe_fd[1]) == -1)
			return (EXIT_FAILURE);
		pipe_fd[1] = -42;
	}
	return (EXIT_SUCCESS);
}
// we fork the child, then child go to
// child_init_pipes_dup, if failed
// exit_failure else parent get out with return 0

pid_t	child_secure_fork(t_command_exec *node, t_utils *utils,
		int *pipe_fd)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		close(utils->old_stdin);
		close(utils->old_stdout);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_init_pipes_dup(node, pipe_fd, utils);
	}
	else if (child == -1)
		return (-1);
	return (child);
}

// if we are not dealing with the last cmd
// we close the pipe_fd[1](WRITE END) return 1 if fail
// we do that because in setup_coming_child_pipes
// we only pipe if this is not the last cmd so we only close
// when there was a pipe before.
// if there was cmd before that one we close previous_pipe
// then give to previous pipe the value of the old READ end
// because the old READ become the new WRITE to complete the pipe

int	setup_next_child(t_utils *utils, int *pipe_fd, int i)
{
	if (i < utils->num_nodes - 1 && pipe_fd[1] != NONE)
	{
		if (close(pipe_fd[1]) == -1)
			return (EXIT_FAILURE);
		pipe_fd[1] = NONE;
	}
	if (utils->previous_pipes != NONE)
	{
		if (close(utils->previous_pipes) == -1)
			return (EXIT_FAILURE);
		utils->previous_pipes = NONE;
	}
	if (i < utils->num_nodes - 1)
	{
		utils->previous_pipes = pipe_fd[0];
		pipe_fd[0] = NONE;
	}
	else if (pipe_fd[0] != NONE)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = NONE;
	}
	return (EXIT_SUCCESS);
}

// everything related to the creation of the right childs
// is done here thanks to a loop that wont stop
// until we checked all nodes bcs one node
// mean one cmd
int	child_maker(t_command_exec *node, t_utils *utils, int i)
{
	int				pipe_fd[2];
	pid_t			child;
	t_command_exec	*head;

	child = -1;
	head = node;
	if (initialize_child_maker(node, utils, pipe_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fork_all_children(node, utils, pipe_fd, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close_heredoc_fds(head);
	return (wait_for_children_and_cleanup(utils, 0, pipe_fd, child));
}
