/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:09 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/25 15:34:13 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/exec.h"

static void close_free_utils(t_utils *utils, size_t i)
{
    	close(utils->old_stdin);
		close(utils->old_stdout);
        if(utils->env)
        {
		    while(utils->env[i])
		    {
			    free(utils->env[i]);
			    utils->env[i] = NULL;
			    i++;
		    }
	    	free(utils->env);
		    free(utils);
        }
        free(utils);
}
static void close_t_command_exec(t_command_exec *node,t_command_exec *tmp, size_t i)
{
    while(node)
	{
		i = 0;
		while(node->cmd_parts[i])
		{
			free(node->cmd_parts[i]);
			node->cmd_parts[i] = NULL;
			i++;
		}
		free(node->cmd_parts);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

void path_finder_fail(t_command_exec *node, t_utils *utils, bool cmd_not_found)
{
	ft_printfd("minishell: %s: command not found\n", node->cmd_parts[0]);
    close_free_utils(utils, 0);
    close_t_command_exec(node, NULL, 0);
    
	exit(CMD_COMMAND_NOT_FOUND);
}
