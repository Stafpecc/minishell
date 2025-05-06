/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:00:29 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/06 11:27:56 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

#include "../include/minishell.h"

// check if it is a built in cmd

bool	built_in_checker(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	else
		return (false);
}

// To count how much commands has been sent
// INFO : I am unsure about the parameter name
int	count_commands(t_command *cmds, bool *is_alone)
{
	int	count;

	count = 0;
	while (cmds)
	{
        count++;
        cmds = cmds->next;
	}
    *is_alone = (count == 1);
	return (count);
}

// exec that does receive a *node 
//TODO also the struct that contain the env and last return
// can remove is_alone if not enough
// space they exist for lisibility purpose

void	exec(t_command *node)
{
	int		number_nodes;
	bool	is_alone;

	number_nodes = count_commands(node, &is_alone);
	if (is_alone == true)
	{
		if (built_in_checker(node->cmd[0]))
		{
			// TODObuilt_in redirect
		}
	}
    //TODO child_maker
}
