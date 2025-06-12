#include "../../include/exec.h"

int redirect_write_browser(t_redirect **redirect, int i)
{
	while (redirect[i])
		{
			if(redirect[i]->append_redirect == FALSE)
				redirect[i]->fd = open(redirect[i]->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644); //secure
			else
				redirect[i]->fd = open(redirect[i]->arg, O_CREAT | O_WRONLY | O_APPEND, 0644); //secure
			if (redirect[i]->fd < 0)
				return (RETURN_FAILURE);
			if (dup2(redirect[i]->fd, STDOUT_FILENO) < 0)
			{
				close(redirect[i]->fd);
				return (RETURN_FAILURE);
			}
			if(close(redirect[i]->fd) == -1) //TORM IF WORKING
				return(RETURN_FAILURE); 
			i++;
		}
	return (RETURN_SUCCESS);
}

int redirect_read_browser(t_redirect **redirect, int i)
{
	while (redirect[i])
		{
			if(redirect[i]->heredoc == FALSE)
				redirect[i]->fd = open(redirect[i]->arg, O_RDONLY); 
			if (redirect[i]->fd < 0)
				return (RETURN_FAILURE);
			if (dup2(redirect[i]->fd, STDIN_FILENO) < 0)
			{
				close(redirect[i]->fd);
				return (RETURN_FAILURE);
			}
			if(close(redirect[i]->fd) == -1) //TORM IF WORKING
				return (RETURN_FAILURE);
			i++;
		}
	return (RETURN_SUCCESS);
}

int	write_dup(t_redirect **redirect, int *pipe_fd)
{
	if(redirect)
	{
		if(redirect_write_browser(redirect, 0))
			return(RETURN_FAILURE);
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
	i = 0; //TORM
	if(redirect)
	{
		if(redirect_read_browser(redirect, 0))
			return (RETURN_FAILURE);
	}	
	if (previous_pipe != NONE && !redirect)
	{
		if (dup2(previous_pipe, STDIN_FILENO))
			return (RETURN_FAILURE);
	}
	else if (!redirect)
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
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
	if(node->redirect_out && write_dup(node->redirect_out, pipe_fd))
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if(pipe_fd[0] != NONE)
		close(pipe_fd[0]);
	if(pipe_fd[1] != NONE)
		close(pipe_fd[1]);
	child_redirect(node, utils);
	exit(EXIT_FAILURE);
}

// It does redirect to the functions that
// would dup2 the right fdsexec went well
// it will close our fds then we go to the
// next part of the process
//TODO when new struct created, update all of it :> (previous pipe, num_nodes)
void	child_init_pipes_dup(t_command_exec *node, int *pipe_fd, t_utils *utils)
{
	if(utils->num_nodes == 1)
		only_child(node, pipe_fd, utils);
	if (read_dup(node->redirect_in, pipe_fd, utils->previous_pipes, 0))
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
	if (pipe_fd[0] != NONE)
		close(pipe_fd[0]);
	if (pipe_fd[1] != NONE)
		close(pipe_fd[1]);
	child_redirect(node, utils);
	exit(EXIT_FAILURE); // FAIL IF EXECVE DOESNT WORK
}
