/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:04:41 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 14:42:57 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <unistd.h>

static void	free_arg_table(t_arg **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (args[i]->arg)
			free(args[i]->arg);
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_commands(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_arg_table(tmp->cmd_parts);
		free_arg_table(tmp->redirect_in);
		free_arg_table(tmp->redirect_out);
		free(tmp);
	}
}

static void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_commands_exec(t_command_exec *cmd)
{
	t_command_exec	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_string_array(tmp->cmd_parts);
		free_redirect_array(tmp->redirect_in);
		free_redirect_array(tmp->redirect_out);
		free(tmp);
	}
}
