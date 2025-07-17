/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:34:09 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 16:17:36 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Function that:
- checks if a command is empty or invalid;
- verifies if the structure is null, if the array of parts is empty,
  or if the first part (the command itself) is missing;
- returns true if nothing is executable, false otherwise.
*/
bool	is_empty_command(t_command *cmd)
{
	if (!cmd)
		return (true);
	if (!cmd->cmd_parts || !cmd->cmd_parts[0])
	{
		if (cmd->redirect_in || cmd->redirect_out)
			return (false);
		return (true);
	}
	return (false);
}

/*
Function that:
- is used when a syntax error is encountered in redirections or tokens;
- displays a clear error message to the user;
- returns a standard failure value to stop or skip the command.
*/
int	return_failure(const char *token, t_utils *utils)
{
	print_syntax_error(token, utils);
	return (RETURN_FAILURE);
}

/*
Function that:
- displays an error message with the problematic token (>, <, etc.);
- updates the global return code with a syntax error;
- is used to indicate that an unexpected token was found during parsing.
*/
void	print_syntax_error(const char *token, t_utils *utils)
{
	utils->last_return = CMD_SYNTAX;
	ft_printfd("minishell: syntax error near unexpected token `%s'\n", token);
}
