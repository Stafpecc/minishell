/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:36:53 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 13:34:28 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Function that:
- analyzes the type of quotes in the given token;
- updates the flags in cmd_part to indicate if the content is
  enclosed in single or double quotes;
- if no quotes are present, resets the flags to false.
*/
void	process_quotes(t_token *token, t_arg *cmd_part)
{
	if (token->type == TOK_SINGLE_QUOTES)
	{
		cmd_part->in_simple_quote = true;
		cmd_part->in_double_quote = false;
	}
	else if (token->type == TOK_DOUBLE_QUOTES)
	{
		cmd_part->in_simple_quote = false;
		cmd_part->in_double_quote = true;
	}
	else
	{
		cmd_part->in_simple_quote = false;
		cmd_part->in_double_quote = false;
	}
}
