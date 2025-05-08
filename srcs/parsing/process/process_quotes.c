/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:36:53 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 15:37:18 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void process_quotes_arg(t_token *tokens, t_arg *arg)
{
	if ((tokens)->type == TOK_SINGLE_QUOTES || (tokens)->type == TOK_DOUBLE_QUOTES)
    {
        arg->in_simple_quote = true;
        arg->in_double_quote = false;
    }
    else
    {
        arg->in_simple_quote = false;
        arg->in_double_quote = true;
    }
}

void process_quotes_cmd(t_token *token, t_cmd_part *cmd_part)
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
