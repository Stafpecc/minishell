/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:41:11 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 13:39:38 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//#include "parsing.h"
#include "exec.h"

void	execute_or_cleanup(t_command_exec *cmd, t_token *token, char *input,
	t_utils *utils)
{
	if (!cmd)
	{
		free(input);
		free_tokens(token);
		return ;
	}
	free(input);
	free_tokens(token);
	if (exec(cmd, utils) == MALLOC_ERROR)
	{
		free_commands_exec(cmd);
		perror("EXEC ERROR");
		exit(EXIT_FAILURE);
	}
	free_commands_exec(cmd);
}
