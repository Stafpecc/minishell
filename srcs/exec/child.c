/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:22:44 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/07 16:53:02 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

// TODO also need a struct with env + last return
void	child_maker(t_command *node, int number_nodes)
{
	int		i;
	int		pipe_fd[2];
	int		previous_pipe;
	pid_t	child;

	previous_pipe = -1;
	while (node)
	{
		if (i < number_nodes - 1)
			pipe(pipe_fd); // TODO protect
		child = fork();    // protect
		if (child == 0)
		{
			if (previous_pipe != -1)
			{
				dup2(previous_pipe, STDIN_FILENO);
				close(previous_pipe);
			}
			else if (node->redirect_in)
				// TODO FUNCTION FOR THAT CASE WHEN REDIRECTIN
				if (pipe_fd[0])
					close(pipe_fd[0]);
			// COMPLETE PATH+ARG+EXECVE
			exit(1); // FAIL IF EXECVE DOESNT WORK
		}
		else
		{
			// parent close what we dont need anymore
			if (previous_pipe != -1)
				close(previous_pipe);
			if (i < number_nodes - 1)
				close(pipe_fd[1]);
			previous_pipe = pipe_fd[0];
			node = node->next;
			i++;
		}
	}
	// TODO WAIT CHILDS WAITPID
}
// exec goes to 2 different path at the moment. first one
// is when there is only 1 cmd that is a built the 2nd one
// is whenever the first condition isnt fullfilled
// TODO introduce struct that hold env + last return value
void	exec(t_command *node)
{
	int number_nodes;
	bool is_alone;

	number_nodes = count_commands(node, &is_alone);
	if (is_alone == true)
	{
		if (built_in_checker(&node->cmd[0]))
		{
			ft_printf("Parent: built_in_checker passed\n"); // TORMASAP
			// TODObuilt_in redirect
		}
		else
			printf("parent: not a single built-in\n"); // TORMASAP
	}

	// TODO child_maker
}