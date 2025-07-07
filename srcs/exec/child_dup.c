/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:55:02 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/01 12:38:41 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// Used if we do only have one cmd
// TODO complete doc about that function
// TORM read up same as child_init
void	only_child(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	if (node->redirect_in && read_dup(node->redirect_in, utils->previous_pipes))
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (node->redirect_out && write_dup(node->redirect_out, pipe_fd))
	{
		close(pipe_fd[0]);
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
// TORM line 134 = if (read_dup(node->redirect_in
//, pipe_fd, utils->previous_pipes)) if no work

void	child_init_pipes_dup(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	if (utils->num_nodes == 1)
		only_child(node, pipe_fd, utils);
	if (read_dup(node->redirect_in, utils->previous_pipes))
	{
		if (utils->previous_pipes != NONE)
			close(utils->previous_pipes);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (write_dup(node->redirect_out, pipe_fd))
	{
		if (utils->previous_pipes != NONE)
			close(utils->previous_pipes);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (utils->previous_pipes != NONE)
		close(utils->previous_pipes);
	if (pipe_fd[0] != NONE && utils->previous_pipes == NONE)
		close(pipe_fd[0]);
	if (pipe_fd[1] != NONE)
		close(pipe_fd[1]);
	child_redirect(node, utils);
}
