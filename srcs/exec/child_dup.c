
#include "../include/exec.h"

// dup the right fd for stdoutput and return 
// an error code if it doesnt work properly
int	outfile_dup(char *redirect, int *pipe_fd, int fd)
{
	if (redirect)
	{
		fd = open(redirect, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			close(fd);
			return (2);
		}
		close(fd);
	}
	else
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO))
			return (2);
	}
	return (0);
}

// dup the right fd for stdinput and return
// an error code if it doesnt work properly
int	infile_dup(char *redirect, int *pipe_fd, int previous_pipe, int fd)
{
	if (redirect)
	{
		fd = open(redirect, O_RDONLY);
		if (fd < 0)
			return (1);
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			close(fd);
			return (2);
		}
		close(fd);
	}
	else if (previous_pipe != -1)
	{
		if (dup2(previous_pipe, STDIN_FILENO))
			return (2);
	}
	else
	{
		if (dup2(pipe_fd[0], STDIN_FILENO))
			return (2);
	}
	return (0);
}

// It does redirect to the functions that
// would dup2 the right fds depending
// of the situation. it is also
// supposed to be completly secured in case of
// errors, once everything went well
// it will close our fds then we go to the
// next part of the process
void	child_init_pipes_dup(t_command *node, int *pipe_fd, int previous_pipe)
{
	if (infile_dup(node->redirect_in, pipe_fd, previous_pipe, 0) != 0)
	{
		if (previous_pipe != -1)
			close(previous_pipe);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (outfile_dup(node->redirect_out, pipe_fd, 0) != 0)
	{
		if (previous_pipe != -1)
			close(previous_pipe);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (previous_pipe != -1)
		close(previous_pipe);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// NEXT STEP COMPLETE PATH+ARG+EXECVE
	exit(EXIT_FAILURE); // FAIL IF EXECVE DOESNT WORK
}