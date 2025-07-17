/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:55:02 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/17 16:15:01 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// Used if we do only have one cmd
// do the same as child_init_pipes_dup
// just the logic here is slighty different since
// since we only get one child
void	only_child(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	if (node->redirect_out && write_dup(node->redirect_out, pipe_fd))
	{
		perror("");
		if (pipe_fd[0] != NONE)
			close(pipe_fd[0]);
		if (pipe_fd[1] != NONE)
			close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (node->redirect_in && read_dup(node->redirect_in, utils->previous_pipes))
	{
		perror("");
		if (pipe_fd[0] != NONE)
			close(pipe_fd[0]);
		if (pipe_fd[1] != NONE)
			close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pipe_fd[0] != NONE)
		close(pipe_fd[0]);
	if (pipe_fd[1] != NONE)
		close(pipe_fd[1]);
	child_redirect(node, utils);
	exit(EXIT_FAILURE);
}

// It does redirect to the functions that
// would dup2 the right fdsexec went well
// it will close our fds then we go to the
// next part of the process

void	multiple_childs(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	if (write_dup(node->redirect_out, pipe_fd))
	{
		perror("");
		if (utils->previous_pipes != NONE)
			close(utils->previous_pipes);
		if (pipe_fd[0] != NONE)
			close(pipe_fd[0]);
		if (pipe_fd[1] != NONE)
			close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (read_dup(node->redirect_in, utils->previous_pipes))
	{
		perror("");
		if (utils->previous_pipes != NONE)
			close(utils->previous_pipes);
		if (pipe_fd[0] != NONE)
			close(pipe_fd[0]);
		if (pipe_fd[1] != NONE)
			close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
}
// go to only_child  if just one node
// else multiple childs dup
// then we close and set to none

void	child_init_pipes_dup(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	if (utils->num_nodes == 1)
		only_child(node, pipe_fd, utils);
	else
		multiple_childs(node, pipe_fd, utils);
	if (close_and_set_none(utils->previous_pipes, pipe_fd) == RETURN_FAILURE)
		path_finder_fail(node, utils, 0, RETURN_FAILURE);
	if (!node->cmd_parts[0])
		exit(EXIT_SUCCESS);
	child_redirect(node, utils);
}
