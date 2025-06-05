// typedef struct s_command {
//     char **cmd;
//     char *redirect_in;
//     char *redirect_out;
//     struct s_command *next;
// } t_command;

// echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

// #include "../include/exec.h"
#include "../../include/exec.h"



// check if it is a built-in cmd
// TODO also need a struct with env + last return

void	child_maker(t_command_exec *node, t_utils *utils)
{
	int		i;
	int		pipe_fd[2]; //TODO add to utils
	//int		previous_pipe; //TORM
	pid_t	child;
	int     status; //TODO add to utils?

	status = 0;
	i = 0;
	utils->previous_pipes = -42; // TODO ask/check if it is init to -42 + make a define for clarity
	// printf("NOMBRE NODES: %d\n", number_nodes); //TODL
	pipe(pipe_fd);
	while (node)
	{
		ft_printfd("TEST\n\n\n\n");

		if (utils->previous_pipes != -42 && i < utils->num_nodes - 1)
		{
			pipe(pipe_fd); // TODO protect
		}
		else if (i == utils->num_nodes - 1) //Necessary for the very last node
			pipe_fd[1] = -42; //FIND A BETTER WAY TO HANDLE THAT CASE
		child = fork(); // protect
		if (child == 0)
			child_init_pipes_dup(node, pipe_fd, utils);
		else
		{
			if (i < utils->num_nodes - 1)
			{
				close(pipe_fd[1]);
			} 
			if (utils->previous_pipes != -42)
				close(utils->num_nodes);
			utils->previous_pipes = pipe_fd[0];
			node = node->next;
			i++;
		}
	}
	close(utils->previous_pipes);
	close(pipe_fd[1]);
	while (waitpid(child, &status, 0) > 0)
		utils->last_return = status >> 8;
	printf("last error_return = %u\n",status >> 8);
		//printf("Test\n");
	// TODO WAIT CHILDS WAITPID
}

//function that will determine which built-in
//we are dealing with then return its return
//that would be the $?
//TODO Ask theo if there is a way to make it better

static int only_child_built_in(t_command_exec *node, t_utils *utils)
{
	if(node->redirect_in)
	{
		if(read_dup(node->redirect_in, 0, utils->previous_pipes, 0))
			{
				return(EXIT_FAILURE);
			}
	}
	if(node->redirect_out)
	{
		if(write_dup(node->redirect_out, 0, 0))
		{
			return(EXIT_FAILURE);
		}
	}
	return (0);
}

int single_built_in(t_command_exec *node, t_utils *utils)
{
	if(node->redirect_in || node->redirect_out)
	{
		if(only_child_built_in(node, utils))
			return(-42); //TODO handle error cases, free everything blabla
	}
	if (!ft_strcmp(node->cmd_parts[0], "cd"))
		return (cd_builtin(node, utils, 0, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "pwd"))
		return (pwd_builtin(node, utils, 0, 4));
	//else if (!ft_strcmp(node->cmd_parts[0], "export"))
		//return (export_builtin(node, utils));
	// else if (!ft_strcmp(node->cmd_parts[0], "unset"))
	// 	return (unset_builtin(node, utils));
	else if (!ft_strcmp(node->cmd_parts[0], "env"))
		return (env_builtin(node, utils, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "exit"))
		return (exit_builtin(node, utils));
	return(-42); //shouldnt even get there at this point
}

// exec that does receive two struct, command_exec(nameWIP)
// and also a struct utils that hold every tools the exec need
// TODO also the struct that contain the env and last return
// can remove is_alone if not enough
// space they exist for lisibility purpose
//TODO LATER include printfd + remove changes done on tarini's printf

void	exec(t_command_exec *node, t_utils *utils)
{
	bool is_alone; //TODO utils?
	//ft_printfd("TEST>>W<WKDK\n\n\n %s",node->redirect_in[0]);

	utils->num_nodes = count_commands(node, &is_alone);
	//printf("num_nodes: %d\n", utils->num_nodes);
	if (is_alone == true)
	{
		if (built_in_checker(node->cmd_parts[0]))
		{
			utils->status = single_built_in(node, utils); //TODO check error
			ft_printfd("Parent: built_in_checker passed\n"); // TORMASAP
															// TODObuilt_in redirect
		}
		else //TORM (probably useless bcs else bellow does the exact samething.)
		{
			//printf("parent: not a single built-in\n"); // TORMASAP
			child_maker(node,utils);
		}
	}
	else
		child_maker(node,utils); //TODO ASK TARINI IF THE PARSING TREAT SOME KIND OF CASES LIKE NOTHING IS SENT FOR EX
	//printf("FAILURE\n");
	return;
}
