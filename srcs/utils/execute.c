/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:41:11 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 15:59:16 by stafpec          ###   ########.fr       */
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
	set_signals();
}
