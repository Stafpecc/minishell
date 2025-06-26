/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:51:58 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/26 14:09:11 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// once the childs are created the parent
// is gonna close everything that need to be closed here
// then it will wait at waitpid and also update last_return
// to hold the last return value of the last child
// then return 0 on success

static int	wait_for_children_and_cleanup(t_utils *utils, int status,
		int *pipe_fd, pid_t child)
{
	// if (utils->previous_pipes >= 0)
	// {
	// 	if (close(utils->previous_pipes) == -1)
	// 		return (EXIT_FAILURE);
	// }
	// if (pipe_fd[1] != MALLOC_ERROR)
	// {
	// 	if (close(pipe_fd[1]) == -1)
	// 		return (EXIT_FAILURE);
	// }
	// close(pipe_fd[0]);
	while (waitpid(child, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			utils->last_return = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			utils->last_return = 128 + WTERMSIG(status);
	}
	close(pipe_fd[0]);
	return (EXIT_SUCCESS);
}
// is previous pipe exist if yes is it not the last cmd?
// if both yes we do a new pipe and secure it
// else if we are at the very last cmd we close
// pipe_fd[1](WRITE END) in a secured way and
// it get value -42 for later comparisons (TODO CHECK
// IF BETTER WAY TO HANDLE THAT CASE)
// then return 0 if successful run

static int	setup_coming_child_pipes(t_utils *utils, int *pipe_fd, int i)
{
	if (utils->previous_pipes != -42 && i < utils->num_nodes - 1)
	{
		if (pipe(pipe_fd) == -1)
			return (EXIT_FAILURE);
	}
	else if (i == utils->num_nodes - 1 && pipe_fd[1] != -42)
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

static pid_t	child_secure_fork(t_command_exec *node, t_utils *utils,
		int *pipe_fd)
{
	pid_t	child;

	child = fork();
	if (child == 0)
		child_init_pipes_dup(node, pipe_fd, utils);
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

static int	setup_next_child(t_utils *utils, int *pipe_fd, int i)
{
	if (i < utils->num_nodes - 1 && pipe_fd[1] != -42)
	{
		if (close(pipe_fd[1]) == -1)
			return (EXIT_FAILURE);
		pipe_fd[1] = -42;
	}
	if (utils->previous_pipes != -42)
	{
		if (close(utils->previous_pipes) == -1)
			return (EXIT_FAILURE);
	}
	utils->previous_pipes = pipe_fd[0];
	return (EXIT_SUCCESS);
}

// everything related to the creation of the right childs
// is done here thanks to a loop that wont stop
// until we checked all nodes bcs one node
// mean one cmd
int	child_maker(t_command_exec *node, t_utils *utils, int i)
{
	int		pipe_fd[2];
	pid_t	child;

	utils->previous_pipes = -42;
	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	while (node)
	{
		if (setup_coming_child_pipes(utils, pipe_fd, i))
			return (EXIT_FAILURE);
		child = child_secure_fork(node, utils, pipe_fd);
		if (child == -1)
			return (EXIT_FAILURE);
		if (setup_next_child(utils, pipe_fd, i))
			return (EXIT_FAILURE);
		node = node->next;
		i++;
	}
	return (wait_for_children_and_cleanup(utils, 0, pipe_fd, child));
}
