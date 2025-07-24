/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_maker_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:56:13 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 13:25:52 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// init the right variables and the first pipe
// before getting into the child loop.
// also check as a security before getting into it

int	initialize_child_maker(t_command_exec *node, t_utils *utils, int *pipe_fd)
{
	if (!node || !utils)
		return (EXIT_FAILURE);
	utils->previous_pipes = NONE;
	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// here we get into the loop
// that will create new process
// each time needed, at first it setup
// then create the process prepare for the next iteration
// go to the next node, then once done return success

int	fork_all_children(t_command_exec *node, t_utils *utils, int *pipe_fd,
		pid_t *child)
{
	int	i;

	i = 0;
	while (node)
	{
		if (setup_coming_child_pipes(utils, pipe_fd, i))
			return (EXIT_FAILURE);
		child_secure_fork(node, utils, pipe_fd, child);
		if (*child == -1)
			return (EXIT_FAILURE);
		if (setup_next_child(utils, pipe_fd, i))
			return (EXIT_FAILURE);
		node = node->next;
		i++;
	}
	return (EXIT_SUCCESS);
}
// close everything once the parent stopped to create
// new childs

void	close_heredoc_fds(t_command_exec *head)
{
	int	j;

	while (head)
	{
		j = 0;
		if (head->redirect_in)
		{
			while (head->redirect_in[j])
			{
				if (head->redirect_in[j]->heredoc)
					close(head->redirect_in[j]->fd);
				j++;
			}
		}
		head = head->next;
	}
}
