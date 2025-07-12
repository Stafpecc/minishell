/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dup_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:44:59 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/01 12:38:25 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// if(close(redirect[i]->fd) == -1) //TORM IF WORKING
// return(RETURN_FAILURE);

#include "../../include/exec.h"

// while loop until we completed to browse the redirect
// array (to create the right amount of open just like
// bash does even if only the last one would be use for the write part

int	redirect_write_browser(t_redirect **redirect, int i)
{
	while (redirect[i])
	{
		if (redirect[i]->append_redirect == FALSE)
		{
			redirect[i]->fd = open(redirect[i]->arg,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else
			redirect[i]->fd = open(redirect[i]->arg,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (redirect[i]->fd < 0)
			return (RETURN_FAILURE);
		if (dup2(redirect[i]->fd, STDOUT_FILENO) < 0)
		{
			close(redirect[i]->fd);
			return (RETURN_FAILURE);
		}
		if (close(redirect[i]->fd) == -1)
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}

// while loop until we completed to browse the redirect
// array (to call the  right amount of open just like
// bash does even if only the last one would be readed
// if(close(redirect[i]->fd) == -1) //TORM IF WORKING
// return(RETURN_FAILURE);

int	redirect_read_browser(t_redirect **redirect, int i)
{
	while (redirect[i])
	{
		if (redirect[i]->heredoc == FALSE)
			redirect[i]->fd = open(redirect[i]->arg, O_RDONLY);
		if (redirect[i]->fd < 0)
			return (RETURN_FAILURE);
		if (dup2(redirect[i]->fd, STDIN_FILENO) < 0)
		{
			close(redirect[i]->fd);
			return (RETURN_FAILURE);
		}
		if (close(redirect[i]->fd) == -1)
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}

// dup the right fd for stdout and return
// an error code if it doesnt work properly

int	write_dup(t_redirect **redirect, int *pipe_fd)
{
	if (redirect)
	{
		if (redirect_write_browser(redirect, 0))
			return (RETURN_FAILURE);
	}
	else if (pipe_fd[1] != NONE)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (2);
	}
	return (RETURN_SUCCESS);
}

// dup the right fd for stdinput and return
// an error code if it doesnt work properly
// TORM read_dup same as bellow
// else if (previous_pipe == NONE)
// {
// if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// return (RETURN_FAILURE);
// }
int	read_dup(t_redirect **redirect, int previous_pipe)
{
	if (redirect)
	{
		if (redirect_read_browser(redirect, 0))
			return (RETURN_FAILURE);
	}
	else if (previous_pipe != NONE)
	{
		if (dup2(previous_pipe, STDIN_FILENO) == -1)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
