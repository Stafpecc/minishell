/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:41:11 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/22 10:16:13 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
		ft_printfd("last_return value = %d\n", utils->last_return);
		free_commands_exec(cmd);
		close(utils->old_stdin);
		close(utils->old_stdout);
		perror("EXEC ERROR");
		exit(EXIT_FAILURE);
	}
	ft_printfd("last_return value = %d\n", utils->last_return);
	free_commands_exec(cmd);
	set_signals();
}
