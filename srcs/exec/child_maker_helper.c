/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_maker_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:56:13 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/16 17:40:27 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	initialize_child_maker(t_command_exec *node, t_utils *utils, int *pipe_fd)
{
	if (!node || !utils)
		return (EXIT_FAILURE);
	utils->previous_pipes = NONE;
	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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
