/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:36:53 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:56:04 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void process_quotes(t_token *token, t_arg *cmd_part)
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
