
//#include "../include/exec.h"
#include "../../include/exec.h"

int	write_dup(t_redirect **redirect, int *pipe_fd, int i)
{
	if(redirect)
	{
		while (redirect[i])
		{
			if(redirect[i]->append_redirect == FALSE)
				redirect[i]->fd = open(redirect[i]->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644); //secure
			else
				redirect[i]->fd = open(redirect[i]->arg, O_CREAT | O_WRONLY | O_APPEND, 0644); //secure
			if (redirect[i]->fd < 0)
				return (1);
			if (dup2(redirect[i]->fd, STDOUT_FILENO) < 0)
			{
				close(redirect[i]->fd);
				return (2);
			}
			close(redirect[i]->fd);
			i++;
		}
	}
	if (pipe_fd[1] != -42 && !redirect)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (2);
	}
	return (RETURN_SUCCESS);
}

// dup the right fd for stdinput and return
// an error code if it doesnt work properly
int	read_dup(t_redirect **redirect, int *pipe_fd, int previous_pipe, int i)
{
	if(redirect)
	{
		while (redirect[i])
		{
			if(redirect[i]->heredoc == FALSE)
				redirect[i]->fd = open(redirect[i]->arg, O_RDONLY); 
			if (redirect[i]->fd < 0)
				return (1);
			if (dup2(redirect[i]->fd, STDIN_FILENO) < 0)
			{
				close(redirect[i]->fd);
				return (2);
			}
			close(redirect[i]->fd);
			i++;
		}
	}	
	if (previous_pipe != -42 && !redirect)
	{
		if (dup2(previous_pipe, STDIN_FILENO))
			return (2);
	}
	else if (!redirect)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (2);
	}
	return (0);
}

// Used if we do only have one cmd
//TODO complete doc about that function
void only_child(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	if(node->redirect_in
		&& read_dup(node->redirect_in, pipe_fd, utils->previous_pipes, 0))
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if(node->redirect_out && write_dup(node->redirect_out, pipe_fd, 0))
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if(pipe_fd[0] != -42)
		close(pipe_fd[0]);
	if(pipe_fd[1] != -42)
		close(pipe_fd[1]);
	child_redirect(node, utils);
	exit(EXIT_FAILURE);
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

	if(utils->num_nodes == 1)
		only_child(node, pipe_fd, utils);
	if (read_dup(node->redirect_in, pipe_fd, utils->previous_pipes, 0))
	{
		if (utils->previous_pipes != -42)
			close(utils->previous_pipes);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (write_dup(node->redirect_out, pipe_fd, 0))
	{
		if (utils->previous_pipes != -42)
			close(utils->previous_pipes);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	ft_printfd("TEST\n\n\n\n");
	if (utils->previous_pipes != -42)
		close(utils->previous_pipes);
	if (pipe_fd[0] != -42)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -42)
		close(pipe_fd[1]);
	child_redirect(node, utils);
	exit(EXIT_FAILURE); // FAIL IF EXECVE DOESNT WORK
}
