/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:27:34 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/13 16:04:33 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/exec.h"

//EXEC does lead to two possibilities
//if the cmd is single AND also a built_in
//then go to path A(single_built_in so no childs)
//else go to path B child_maker to make right nbr of childs
//one cmd = one child

int	exec(t_command_exec *node, t_utils *utils)
{
	//int return_code;
	
	utils->num_nodes = count_commands(node);
	if (utils->num_nodes == 1 && built_in_checker(node->cmd_parts[0]))
	{
		utils->status = single_built_in(node, utils);
			return(utils->status);
	}
	else
	{
		if(child_maker(node, utils, 0))
			return(RETURN_FAILURE); //TODO EXIT PROPERLY ASK THEO HOW TO DEAL WITH THAT
	}
	return(RETURN_SUCCESS);
}
