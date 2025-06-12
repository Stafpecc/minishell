/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:09:30 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/12 11:22:37 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"


//if redirection will redirect 
//to dup properly, if fail return 1 else 0
static int single_built_in_redirections(t_command_exec *node, t_utils *utils)
{
	if(node->redirect_in)
	{
		if(read_dup(node->redirect_in, 0, utils->previous_pipes, 0))
			return(EXIT_FAILURE);
	}
	if(node->redirect_out)
	{
		if(write_dup(node->redirect_out, 0, 0))			
			return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//function that will do the right redirect if needed
//then determine which built-in we are dealing with
//then return the return value of the built-in function

int single_built_in(t_command_exec *node, t_utils *utils)
{
	if(node->redirect_in || node->redirect_out)
	{
		if(single_built_in_redirections(node, utils))
			return(MALLOC_ERROR);
	}
	if (!ft_strcmp(node->cmd_parts[0], "cd"))
		return (cd_builtin(node, utils, 0, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "pwd"))
		return (pwd_builtin(node, utils, 0, 4));
	//else if (!ft_strcmp(node->cmd_parts[0], "export"))
	//	return (export_builtin(node, utils));
	//else if (!ft_strcmp(node->cmd_parts[0], "unset"))
	//	return (unset_builtin(node, utils));
	else if (!ft_strcmp(node->cmd_parts[0], "env"))
		return (env_builtin(node, utils, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "exit"))
		return (exit_builtin(node, utils));
	return(MALLOC_ERROR); //shouldnt even get there at this point
}