
//#include "../include/exec.h"
#include "../../include/exec.h"

// dup the right fd for stdoutput and return 
// an error code if it doesnt work properly
int	write_dup(char *redirect, int *pipe_fd, int fd)
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
	else if (pipe_fd[1] != -42)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			return (2);
		}
			
	}
	return (0);
}

// dup the right fd for stdinput and return
// an error code if it doesnt work properly
int	read_dup(char *redirect, int *pipe_fd, int previous_pipe, int fd)
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
	else if (previous_pipe != -42)
	{
		if (dup2(previous_pipe, STDIN_FILENO))
			return (2);
	}
	else
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			//perror("test1%\n");
			return (2);
		}
	}
	return (0);
}
// Used if we do only have one cmd
//TODO complete doc about that function
void only_child(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	if(node->redirect_in)
		if(read_dup(node->redirect_in, pipe_fd, utils->previous_pipes, 0))
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				exit(EXIT_FAILURE);
			}

	if(node->redirect_out)
	{
		if(read_dup(node->redirect_out, pipe_fd, utils->previous_pipes, 0))
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	child_redirect(node, utils);
	exit(EXIT_FAILURE); // FAIL IF EXECVE DOESNT WORK
}

// It does redirect to the functions that
// would dup2 the right fds depending
// of the situation. it is also
// supposed to be completly secured in case of
// errors, once everything went well
// it will close our fds then we go to the
// next part of the process
//TODO when new struct created, update all of it :> (previous pipe, num_nodes)
void	child_init_pipes_dup(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	ft_printf("redirect_in = %s, redirect_out = %s \n", node->redirect_in, node->redirect_out);
	if(utils->num_nodes == 1)
		only_child(node, pipe_fd, utils);

	if (read_dup(node->redirect_in, pipe_fd, utils->previous_pipes, 0) != 0)
	{
		//perror("test");
		if (utils->previous_pipes != -42)
			close(utils->previous_pipes);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (write_dup(node->redirect_out, pipe_fd, 0) != 0)
	{
		if (utils->previous_pipes != -42)
			close(utils->previous_pipes);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (utils->previous_pipes != -42)
		close(utils->previous_pipes);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	child_redirect(node, utils);
	exit(EXIT_FAILURE); // FAIL IF EXECVE DOESNT WORK
}