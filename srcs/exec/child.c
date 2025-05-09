/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:22:44 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/08 07:22:51 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"


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