/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:41:11 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/25 18:41:26 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

void	execute_or_cleanup(t_command_exec *cmd, t_token *token, char *input, t_utils *utils)
{
	if (cmd)
	{
		if (exec(cmd, utils) == MALLOC_ERROR)
		{
			perror("EXEC ERROR\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		free(input);
		free_tokens(token);
		return ;
	}
	free(input);
	free_tokens(token);
	free_commands_exec(cmd);
}
