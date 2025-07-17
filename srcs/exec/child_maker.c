/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:51:58 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/17 13:26:05 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
//#include <stdlib.h>

// is previous pipe exist if yes is it not the last cmd?
// if both yes we do a new pipe and secure it
// else if we are at the very last cmd we close
// pipe_fd[1](WRITE END) in a secured way and
// it get value NONE for later comparisons
// to avoid double close
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
		pipe_fd[1] = NONE;
	}
	return (EXIT_SUCCESS);
}

static void	close_heredoc(t_redirect **redirect)
{
	int	i;

	i = 0;
	if (redirect)
	{
		while (redirect[i] && redirect[i]->fd)
		{
			if (redirect[i]->heredoc)
				close(redirect[i]->fd);
			i++;
		}
	}
}

// we fork the child, then child go to
// close unecessary open fds
// set the signal accordingly
// child_init_pipes_dup, if failed
// exit_failure else parent get out with return 0
pid_t	child_secure_fork(t_command_exec *node, t_utils *utils,
		int *pipe_fd, pid_t *child)
{
	*child = fork();
	if (*child == 0)
	{
		close(utils->old_stdin);
		close(utils->old_stdout);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_init_pipes_dup(node, pipe_fd, utils);
	}
	close_heredoc(node->redirect_in);
	return (*child);
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
// until we checked all nodes bcs 
// node = cmd 
int	child_maker(t_command_exec *node, t_utils *utils)
{
	int				pipe_fd[2];
	pid_t			child;
	t_command_exec	*head;

	child = -1;
	head = node;
	if (initialize_child_maker(node, utils, pipe_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fork_all_children(node, utils, pipe_fd, &child) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close_heredoc_fds(head);
	return (wait_for_children_and_cleanup(utils, 0, pipe_fd, child));
}
