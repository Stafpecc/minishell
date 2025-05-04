/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:04:41 by tarini            #+#    #+#             */
/*   Updated: 2025/05/04 16:06:29 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void free_commands(t_command *cmd)
{
	t_command *tmp;
	int i;

	i = 0;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp->cmd);
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(tmp->redirect_in);
		free(tmp->redirect_out);
		free(tmp);
	}
}
