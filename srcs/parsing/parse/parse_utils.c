/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:34:09 by tarini            #+#    #+#             */
/*   Updated: 2025/05/31 17:39:48 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

bool	is_empty_command(t_command *cmd)
{
	return (!cmd || !cmd->cmd_parts || !cmd->cmd_parts[0]);
}

int	return_failure(const char *token, t_utils *utils)
{
	print_syntax_error(token, utils);
	return (RETURN_FAILURE);	
}

void print_syntax_error(const char *token, t_utils *utils)
{
	utils->last_return = CMD_INVALID_ARGUMENT;
	ft_printfd("minishell: syntax error near unexpected token `%s'\n", token);
}
