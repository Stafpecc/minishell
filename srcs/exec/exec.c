/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:27:34 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/10 18:00:07 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/exec.h"

static int parent_waiting(t_utils *utils, int status, pid_t child, int *pipe_fd)
{
	close(utils->previous_pipes);  //PROTECT TOO
	if (pipe_fd[1] != -42)
		close(pipe_fd[1]); //PROTECT TOO
	close(pipe_fd[0]); //PROTECT TOO
	while (waitpid(child, &status, 0) > 0)
		utils->last_return = status >> 8;
	printf("last error_return = %u\n",status >> 8); //TORM
	return(EXIT_SUCCESS);
}

int	child_maker(t_command_exec *node, t_utils *utils, int i)
{
	int		pipe_fd[2];
	pid_t	child;

	utils->previous_pipes = -42; //TODO make a define for clarity
	if (pipe(pipe_fd) == -1) //TODO create free function
		return(EXIT_FAILURE);
	while (node)
	{
		if (utils->previous_pipes != -42 && i < utils->num_nodes - 1)
		{
			if (pipe(pipe_fd) == -1)
				return(EXIT_FAILURE);
		}
		else if (i == utils->num_nodes - 1)
		{
			close (pipe_fd[1]); //TODO PROTECT THIS TOO
			pipe_fd[1] = -42; //FIND A BETTER WAY TO HANDLE THAT CASE LIKE DEFINE
		} 
		child = fork(); // protect
		if (child == 0)
		{
			child_init_pipes_dup(node, pipe_fd, utils);
		}
		else if (child == -1)
			return(EXIT_FAILURE);
		else
		{
			if (i < utils->num_nodes - 1)
			{
				close(pipe_fd[1]); //PROTECT HUH
			} 
			if (utils->previous_pipes != -42)
				close(utils->previous_pipes); //PROTECT TOO
			utils->previous_pipes = pipe_fd[0];
			node = node->next;
			i++;
		}
	}
	return (parent_waiting(utils, 0, child, pipe_fd));
}



//EXEC does lead to two possibilities
//if the cmd is single AND also a built_in
//then go to path A(single_built_in)
//else go to child_maker to make right nbr of childs

int	exec(t_command_exec *node, t_utils *utils)
{
	utils->num_nodes = count_commands(node);
	if (utils->num_nodes == 1 && built_in_checker(node->cmd_parts[0]))
	{
		utils->status = single_built_in(node, utils);
		if (utils->status == MALLOC_ERROR)
			return(EXIT_FAILURE);//TODO EXIT PROPERLY ASK THEO HOW TO DEAL WITH THAT
	}
	else
	{
		if(child_maker(node, utils, 0))
			return(EXIT_FAILURE); //TODO EXIT PROPERLY ASK THEO HOW TO DEAL WITH THAT
	}
	return(EXIT_SUCCESS);
}
