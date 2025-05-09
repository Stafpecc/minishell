/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:22:44 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/08 17:17:10 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
//TODO ENUM for cases to make it more readable
//TODO think about if I have to close/free some stuff when it is the child
//TODO IDEA I HAD ABOUT THE VALUE OF STDOUT_FILENO)
int		open_dup_close(char *redirect, int *pipe_fd, int previous_pipe, int cases)
{
	int fd;

	fd = 0;
	if (redirect)
	{
		fd = open(redirect); //secure
		if (cases == 0)
			dup2(fd, STDIN_FILENO); //check comment secure
		else if (cases == 1)
			dup2(fd, STDOUT_FILENO); //TODO else if fd= error handle error
		close(fd);
	}
	else if (previous_pipe != -1)
		dup2(previous_pipe, STDIN_FILENO);
	else if (cases == 0)
		dup2(pipe_fd[0], STDIN_FILENO); //TODO? maybe remove and test if it work without
	else if (cases == 1)
		dup2(pipe_fd[1], STDOUT_FILENO);
	
}

void	init_child(t_command *node, int *pipe_fd, int previous_pipe)
{
	int fd;

	open_dup_close(node->redirect_in, pipe_fd, previous_pipe, 0); //TODO define for cases 0
	open_dup_close(node->redirect_in, pipe_fd, previous_pipe, 1);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (previous_pipe != -1)
		close(previous_pipe);
	// COMPLETE PATH+ARG+EXECVE
	exit(1); // FAIL IF EXECVE DOESNT WORK
}